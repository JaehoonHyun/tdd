package main

import (
    "testing"

    . "github.com/onsi/ginkgo" //internal로 쓰겠다. 패키지명을 적지 않겠ㄷ.
    . "github.com/onsi/gomega"

)

func TestGinkgo(t *testing.T) {
    RegisterFailHandler(Fail)
    RunSpecs(t, "Test functions Suite")
}

/*
하나를 서술한다. 이름은 "Test functions"
서술자 안에 주변상황를 만든다. 이름은 "sample"
실제 워킹하는 물체를 만든다. 이름은 "one shoule return 1"
이 물체는 1을 기대한다.


*/
var _ = Describe("Test functions",
    func(){
        Context("sample", func() {
            It("one should return 1", func(){
                Expect(1).To(Equal(one()))
            })

            It("name should return name", func(){
                Expect("name").To(Equal(name()))
            })
        })
    },)