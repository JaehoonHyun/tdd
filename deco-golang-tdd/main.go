package main

import (
	"log"
)

type desert interface {
	eat()
}

type icecream struct {
	desert
}

func (i *icecream) eat() {
	log.Print("icecream ")
}

type choco struct {
	desert
	d desert
}

func (c *choco) eat() {
	log.Print("choco ")
	c.d.eat()
}

type syrup struct {
	desert
	d desert
}

func (s *syrup) eat() {
	log.Print("syrup ")
	s.d.eat()
}

func main() {

	desert := syrup{d: &choco{d: &icecream{}}}
	desert.eat()

}
