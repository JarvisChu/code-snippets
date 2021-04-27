package main

import(
	"fmt"
	"io/ioutil"
	"net/http"
)

func index(w http.ResponseWriter, r *http.Request) {
	fmt.Println("index")
	data, _ := ioutil.ReadFile("index.html")
	fmt.Fprint(w, string(data))
}

func main(){
	http.Handle("/js/", http.StripPrefix("/js/", http.FileServer(http.Dir("js"))))
	http.HandleFunc("/", index)	
	http.ListenAndServe(":8002", nil)
}