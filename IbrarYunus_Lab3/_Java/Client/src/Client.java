
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;


import javax.swing.JOptionPane;

/**
 * Trivial client for the date server.
 */
public class Client {

    /**
     * Runs the client as an application.  First it displays a dialog
     * box asking for the IP address or hostname of a host running
     * the date server, then connects to it and displays the date that
     * it serves.
     */
    public static void main(String[] args) throws IOException {
    	System.out.println("Java based Client");
    	
        Socket s = new Socket("127.0.0.1", 5556);
        BufferedReader input =
        new BufferedReader(new InputStreamReader(s.getInputStream()));
        
        //Server sends file name here
//        String fileName = input.readLine();
//        System.out.println("File Name: " + fileName);
//        
        
        // Server sends file size here
//        String size = input.readLine();
//        System.out.println("File Size: " + size);
        
        //Server should send file here
        byte[] buffer = new byte[4096];
        ///Buffered input stream from the sockets
        BufferedInputStream inStream = new BufferedInputStream(s.getInputStream());
        //Buffered output stream to the file
        FileOutputStream outStream = new FileOutputStream("temp.dat");
        ///Actual File Transfer
        for (int read = inStream.read(buffer); read >= 0; read = inStream.read(buffer))
            outStream.write(buffer, 0, read);
        inStream.close();
        outStream.close();
        		
        System.out.println("File Downloaded Sucessfully");
        System.exit(0);
    }
}
