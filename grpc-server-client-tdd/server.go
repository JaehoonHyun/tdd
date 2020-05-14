//go:generate protoc -I ../helloworld --go_out=plugins=grpc:../helloworld ../helloworld/helloworld.proto


package main

import
(
    "context"
    "log"
    "net"

    "google.golang.org/grpc"
    pb "helloworld"
    pbBook "books"
)

const
(
    port = ":50051"
)

//embeding
type server struct {
    pb.UnimplementedGreeterServer
    pbBook.UnimplementedBookerServer
}

// overloading
func (s *server) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloReply, error) {
    log.Printf("Recevied: %v", in.GetName())
    return &pb.HelloReply{ Message: "Hello" + in.GetName()}, nil
}

// overloading
func (s *server) Borrow(ctx context.Context, req *pbBook.Borrower) (*pbBook.Status, error) {

    log.Printf("Recevied: %v", req.Book.GetName())
    log.Printf("Recevied: %v", req.Person.GetName())

    return &pbBook.Status{ Message: "Hello " + req.Book.GetName() + " / " + req.Person.GetName()}, nil

}

func main() {
    lis, err := net.Listen("tcp", port)
    if err != nil {
        log.Fatalf("failed to listen : %v", err)
    }

    s := grpc.NewServer()
    pb.RegisterGreeterServer(s, &server{})
    pbBook.RegisterBookerServer(s, &server{})

    if err := s.Serve(lis); err != nil {
        log.Fatalf("failed to serve: %v", err)
    }
}
