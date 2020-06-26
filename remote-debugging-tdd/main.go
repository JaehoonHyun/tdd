package main

import (
	"log"
	"net/http"
	"strconv"
)

const port = "8000"

func main() {
	http.HandleFunc("/fib", fibHandler)

	log.Printf("listening on port %s", port)
	log.Fatalln(http.ListenAndServe(":"+port, nil))
}

func fibHandler(w http.ResponseWriter, r *http.Request) {
	ns, ok := r.URL.Query()["num"]
	if !ok || len(ns) < 0 {
		log.Println("param 'num' is missing")
		return
	}
	n0, err := strconv.Atoi(ns[0])
	if err != nil {
		log.Printf("invalid number: %v", err)
		return
	}
	fb := strconv.Itoa(fib(n0))
	w.Write([]byte(fb + "\n"))
}

func fib(n int) int {
	a, b := 1, 1
	for i := 0; i < n-2; i++ {
		a, b = b, a+b
	}
	return b
}
