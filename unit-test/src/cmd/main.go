package main

import (
	"encoding/json"
	"io"
	"net/http"
	"unit-test/src/router"
)

type Error struct {
	Error string `json:"Error"`
}

func main() {
	rout := router.Server{
		Ip:   "127.0.0.1",
		Port: "2003",
	}

	rout.Append_handler(router.HandlerFuncStruct{
		Name: "/auth/login",
		Function: func(w http.ResponseWriter, r *http.Request) {
			byte, _ := io.ReadAll(r.Body)
			w.Write(byte)
		},
	})
	rout.Append_handler(router.HandlerFuncStruct{
		Name: "/auth/register",
		Function: func(w http.ResponseWriter, r *http.Request) {
			byte, _ := io.ReadAll(r.Body)
			w.Write(byte)
		},
	})

	rout.Append_handler(router.HandlerFuncStruct{
		Name: "/",
		Function: func(w http.ResponseWriter, r *http.Request) {
			e := Error{
				Error: "Invalid address",
			}
			json, _ := json.Marshal(e)
			w.Write(json)

			w.WriteHeader(http.StatusOK)
		},
	})

	rout.Run_server()
}
