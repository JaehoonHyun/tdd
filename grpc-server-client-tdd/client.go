package main

import
(
    "log"
    "os"
    "time"
    "context"
    
    "google.golang.org/grpc"
    pb "helloworld"
    pbBook "books"
  	timestamp "github.com/golang/protobuf/ptypes"

)

const 
(
    address = "localhost:50051"
    defaultname = "world"
)

func main() {
    conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithBlock())
    if err != nil {
        log.Fatalf("did not connected : %v", err)
    }
    defer conn.Close()

    c := pb.NewGreeterClient(conn)
    c2 := pbBook.NewBookerClient(conn)

    name := defaultname

    if len(os.Args) > 1 {
        name = os.Args[1]
    }

    ctx, cancel := context.WithTimeout(context.Background(), time.Second)
    defer cancel()

    r, err := c.SayHello(ctx, &pb.HelloRequest{Name: name})
    if err != nil {
        log.Fatalf("could not greet:%v", err)
    }
    log.Printf("Greeting: %s", r.GetMessage())

    // Members := []struct {
	// 		Name    string `json:"name"`
	// 		Address string `json:"address"`
	// 	}{
	// 		{
	// 			Name:    "Ipfix_pool:4739",
	// 			Address: "Ipfix_pool",
	// 		},
    //         {
	//             Name:    "Ipfix_pool:4239",
	// 			Address: "Ipfix_pool",
    //         },
	// 	}

    book := pbBook.Book{Name: "development c++", Id: 12322}
    person := pbBook.Person{ Name: "jaehoonhyun", 
                             Id: 999999, 
                             Email:"jaehoon@samsung.com", 
                             Phones: []*pbBook.Person_PhoneNumber{
                                        &pbBook.Person_PhoneNumber{   
                                            Number: "1-2-3",
                                            Type: pbBook.Person_MOBILE,
                                        }, 
                                        &pbBook.Person_PhoneNumber{
                                            Number: "4-5-6",
                                            Type: pbBook.Person_MOBILE,
                                        },
                                    },
                            LastUpdated: timestamp.TimestampNow(),
                            }

    //return struct Status
    r2, err := c2.Borrow(ctx, &pbBook.Borrower{Book: &book, Person:&person, Id:"jaehoon.hyun"});
    if err != nil {
        log.Fatalf("could not Borrow:%v", err)
    }
    log.Printf("Status: %s", r2.GetMessage())


}

