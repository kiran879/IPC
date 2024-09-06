# IPC
System Programming Project: IPC Mechanisms in C

Overview

This project is a demonstration of Inter-Process Communication (IPC) mechanisms implemented in C. It showcases the use of four different IPC methods—pipes, FIFOs, message queues, and shared memory—to facilitate communication between clients, a server, and vendors.

Project Description

The system involves a server-client-vendor architecture that utilizes different IPC (Inter-Process Communication) mechanisms for communication between the components:

    Client: Requests services from the server.
        IPC Mechanism (Client to Server): FIFO (Named Pipes) is used for communication between the client and server. This allows clients, which may not share a common ancestor with the server, to send requests through a named pipe that the server can access.

    Server: Validates requests from clients and forwards valid requests to the vendors. Once the vendors process the requests, the server receives the results and sends them back to the respective clients.
        IPC Mechanism (Server to Vendors): Pipes are used for communication between the server and vendors. As the server spawns vendor processes, pipes allow efficient communication between the server (parent) and vendor processes (child).
        IPC Mechanism (Vendor to Server): Shared Memory is used for transferring the results from vendors back to the server. Shared memory allows both the server and vendors to directly access and modify a common memory space, ensuring high performance and efficiency for this communication.
        IPC Mechanism (Server to Client): Message Queues are used for sending processed results back to the client. The server sends messages to a queue where the intended client can retrieve them.

    Vendors: Process requests sent by the server and return the results using shared memory. This enables vendors to handle multiple client requests efficiently.
