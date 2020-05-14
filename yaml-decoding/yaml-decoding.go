package main

import (
	"bufio"
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"strings"
	"unicode"

	"gopkg.in/yaml.v2"
)

type LineReader struct {
	reader *bufio.Reader
}

// Read returns a single line (with '\n' ended) from the underlying reader.
// An error is returned iff there is an error with the underlying reader.
func (r *LineReader) Read() ([]byte, error) {
	var (
		isPrefix bool  = true
		err      error = nil
		line     []byte
		buffer   bytes.Buffer
	)

	for isPrefix && err == nil {
		line, isPrefix, err = r.reader.ReadLine()
		buffer.Write(line)
	}
	buffer.WriteByte('\n')
	return buffer.Bytes(), err
}

type Reader interface {
	Read() ([]byte, error)
}

type YAMLReader struct {
	reader Reader
}

func NewYAMLReader(r *bufio.Reader) *YAMLReader {
	return &YAMLReader{
		reader: &LineReader{reader: r},
	}
}

const yamlSeparator = "\n---"
const separator = "---"

// Read returns a full YAML document.
func (r *YAMLReader) Read() ([]byte, error) {
	var buffer bytes.Buffer
	for {
		line, err := r.reader.Read()
		if err != nil && err != io.EOF {
			return nil, err
		}

		sep := len([]byte(separator))
		if i := bytes.Index(line, []byte(separator)); i == 0 {
			// We have a potential document terminator
			i += sep
			after := line[i:]
			if len(strings.TrimRightFunc(string(after), unicode.IsSpace)) == 0 {
				if buffer.Len() != 0 {
					return buffer.Bytes(), nil
				}
				if err == io.EOF {
					return nil, err
				}
			}
		}
		if err == io.EOF {
			if buffer.Len() != 0 {
				// If we're at EOF, we have a final, non-terminated line. Return it.
				return buffer.Bytes(), nil
			}
			return nil, err
		}
		buffer.Write(line)
	}
}

type TypeMeta struct {
	// +optional
	APIVersion string `json:"apiVersion,omitempty" yaml:"apiVersion,omitempty" protobuf:"bytes,1,opt,name=apiVersion"`
	// +optional
	Kind string `json:"kind,omitempty" yaml:"kind,omitempty" protobuf:"bytes,2,opt,name=kind"`
}

func main() {
	fmt.Println("vim-go")
	cfgPath := "/home/jaehoon/go-tdd/yaml-decoding/hello.yaml"
	b, err := ioutil.ReadFile(cfgPath)

	yamlBytes := b
	buf := bytes.NewBuffer(yamlBytes)
	reader := NewYAMLReader(bufio.NewReader(buf))
	b, err = reader.Read()
	typeMetaInfo := TypeMeta{}
	if err = yaml.Unmarshal(b, &typeMetaInfo); err != nil {
		fmt.Printf("yaml Unmarshal fail %v\n", err)
	}
	fmt.Printf("yaml Unmarshal success %v\n", typeMetaInfo)
}
