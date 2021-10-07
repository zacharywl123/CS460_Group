package JavaEchoServer.src.multi_thread;

import java.io.IOException;
import java.net.ServerSocket;

import java.util.logging.Level;
import java.util.logging.Logger;

public class EchoServerMultithreaded {

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
                EchoServerMultithreaded echoServer = new EchoServerMultithreaded(8881);

                // fire up server loop
                echoServer.runServerLoop();
        }
}
