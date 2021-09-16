import java.io.DataInputStream;
import java.io.DataOutputStream;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

import java.util.logging.Level;
import java.util.logging.Logger;

public class EchoServerMultithreaded {

        /*
         * We define an inner class, which extends the Thread class
         */
        class EchoThread extends Thread {
        
                
                Socket clientSocket;
                
                public EchoThread(Socket clientSocket) {
                        this.clientSocket = clientSocket;
                }
                
                public void run() {

                        DataInputStream fromClient = null;
                        DataOutputStream toClient = null;

                        int charFromClient = 0;

                        boolean keepGoing = true;

                        // show that we are connected to client
                        System.out.println("Client connected ...");

                        // first get the streams
                        try {

                                fromClient = new DataInputStream(clientSocket.getInputStream());
                                toClient = new DataOutputStream(clientSocket.getOutputStream());

                        } catch (IOException e) {

                                System.err.println("Error opening network streams");
                                return;
                        }

                        // now talk to the client
                        while (keepGoing) {

                                try {

                                        charFromClient = fromClient.readByte();
                                        System.out.print((char) charFromClient);

                                } catch (IOException e) {

                                        System.err.println("Error reading character from client");
                                        return;
                                }

                                try {

                                        toClient.writeByte(charFromClient);

                                } catch (IOException e) {

                                        System.err.println("Error writing character to client");
                                        return;
                                }

                                if (charFromClient == 'q') {

                                        System.out.println("\nBailing out!");
                                        keepGoing = false;
                                }
                        }

                        try {
                                clientSocket.close();

                        } catch (IOException e) {
                                System.err.println("Error closing socket to client");
                        }                               
                }
        }
        
        
        
        private static ServerSocket serverSocket;
        private static int port;

        public EchoServerMultithreaded(int port) {
        	
		

                try {

                        EchoServerMultithreaded.port = port;
                        EchoServerMultithreaded.serverSocket = new ServerSocket(port);

                } catch (IOException ex) {

                        Logger.getLogger(EchoServerMultithreaded.class.getName()).log(Level.SEVERE, null, ex);
                        System.err.println("Error starting server on port " + port);
                        System.exit(1);
                }

                EchoServerMultithreaded.port = port;
        }

        public void runServerLoop() throws IOException {

                System.out.println("Echo server started");
                while (true) {

                        System.out.println("Waiting for connections on port #" + port);
                        
                        /*
                         * We instantiate a new thread, and starts its execution.
                         */
                        new EchoThread(serverSocket.accept()).start();
                }
        }


        public static void main(String args[]) throws Exception {

                // create instance of echo server

                // note that hardcoding the port is bad, here we do it just for simplicity reasons
                EchoServerMultithreaded echoServer = new EchoServerMultithreaded(23657);

                // fire up server loop
                echoServer.runServerLoop();
        }
}
