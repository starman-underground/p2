import java.io.*;
import java.net.*;

public class Log {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java Client <port> <message>");
            return;
        }

        String hostname = "localhost";	// log server hostname
        int port = Integer.parseInt(args[0]);	// server port
        String message = args[1];	// message to log

        try (
            Socket socket = new Socket(hostname, port);	// connect to the server
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        ) {

            // ######################
            // ### message is our original message
            // ### Convert any whitespace to spaces
            // ### Modify the messsage to include the proof-of-work (Pow+':'+message)
            // ######################

            String outmessage = message;

            System.out.println("sending: " + outmessage);  // debug: print the message
            out.println(outmessage); 	// Send the message to the server

            // Receive the confirmation message from the server
            String response = in.readLine();
            System.out.println("Server response: " + response);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
