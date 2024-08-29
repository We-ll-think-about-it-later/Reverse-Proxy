package router

import "net/http"

type HandlerFuncStruct struct {
	Name     string
	Function func(w http.ResponseWriter, r *http.Request)
}

type Server struct {
	Ip       string
	Port     string
	handlers []HandlerFuncStruct
}

func (s *Server) Run_server() {
	for i := 0; i < len(s.handlers); i++ {
		http.HandleFunc(s.handlers[i].Name, s.handlers[i].Function)
	}
	http.ListenAndServe((s.Ip + ":" + s.Port), nil)
}

func (s *Server) Append_handler(handler HandlerFuncStruct) {
	s.handlers = append(s.handlers, handler)
}
