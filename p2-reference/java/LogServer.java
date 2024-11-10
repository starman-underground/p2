import java.io.*;
import java.net.*;

public class LogServer {

    public static void main(String[] args) {
        try {
            // Create a server socket and bind to any available port
            ServerSocket serverSocket = new ServerSocket(0);
            int port = serverSocket.getLocalPort();
            System.out.println("LogServer listening on port: " + port);

            while (true) { 	// accept client connections
                Socket clientSocket = serverSocket.accept();
                System.out.println("Client connected.");

                handleClient(clientSocket);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        try (
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
        ) {
            String message = in.readLine(); 	// Read the string sent by the client
            System.out.println("Received: " + message);

            // ########## YOUR CODE HERE ############
            // ### Validate the the PoW in the message
            // ### Stril the PoW from the message
            // ### Read the last hash from loghead.txt
            // ### Create the full line for the log entry
            // ### Compute its hash
            // ### Append the line to the log
            // ### Update loghead.txt
            // ### Add error checking
            // #######################################


            // Append the string to log.txt
            try (BufferedWriter logWriter = new BufferedWriter(new FileWriter("log.txt", true))) {
                logWriter.write(message);
                logWriter.newLine();
            } catch (IOException e) {
                e.printStackTrace();
            }

            // Send confirmation message back to the client
            System.out.println("sending resonse: ok");
            out.println("ok");
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

