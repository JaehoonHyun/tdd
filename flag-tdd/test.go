package main

import (
	"flag"
	"fmt"
)

func main() {

	fmt.Println("vim-go")
	flagSet := &flag.FlagSet{}
	AdvertiseAddress := "127.0.0.1"
	flagSet.StringVar(&AdvertiseAddress, "advertise-address", AdvertiseAddress, "Description")
	fmt.Printf("%v\n", flagSet)
	fmt.Printf(AdvertiseAddress + "\n")

	flagSet.Set("advertise-address", "10.96.0.10")
	fmt.Printf(AdvertiseAddress + "\n")
}
