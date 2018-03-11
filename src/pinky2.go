package main

/*
#include <stdio.h>
#include <stdlib.h>
*/
import "C"
import "unsafe"

//export uzer_func4
func uzer_func4() *C.char {
  str := C.CString("Hello World")
  return str
}

//export Gfree
func Gfree(str *C.char) {
  defer C.free(unsafe.Pointer(str))
}

func main() {}
