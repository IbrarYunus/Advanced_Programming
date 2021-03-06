import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

import javax.swing.JOptionPane;

/**
 * A TCP server that runs on port 9090.  When a client connects, it
 * sends the client the current date and time, then closes the
 * connection with that client.  Arguably just about the simplest
 * server you can write.
 */
public class Server {

    /**
     * Runs the server.
     */
    public static void main(String[] args) throws IOException 
    {
    	//Variables
    	long size;
    	////
    	
    	System.out.println("Server Intialized\n");
    	System.out.println("Grabbing a Socket");
    	ServerSocket listener = new ServerSocket(5556);
        try {
            while (true) 
            {
            	System.out.println("Listener Initiated");
                Socket socket = listener.accept();
                System.out.println("Connection Accepted");
                try {
                	String fileName = JOptionPane.showInputDialog("Enter File Name");
                	//size = _GetFileSize(fileName);
                	
                    //PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    
                   
                    //Sending File Name
                    //System.out.println("Sending File Name");
                    //out.println(fileName);
                    
                    //Sleeping for one second
//                    System.out.println("1 second sleep");
//                    try {
//                    	  Thread.sleep(1000);
//                    	} catch (InterruptedException ie) {
//                    	   
//                    	}
//                    
                    ///Sending File Size
//                    System.out.println("Sending File Size");
//                    out.println(size);
//                    
                    //Sleeping for one second
//                    System.out.println("1 second sleep");
//                    try {
//                    	  Thread.sleep(1000);
//                    	} catch (InterruptedException ie) {
//                    	   
//                    	}
                    
                    ///Try to send File
                    System.out.println("Try to Send  File");
                    File file = new File(fileName);
                    //Output Stream from socket
                    final BufferedOutputStream outStream = new BufferedOutputStream(socket.getOutputStream());
                    //Input stream from file
                    BufferedInputStream inStream = new BufferedInputStream(new FileInputStream(file));
                    byte[] buffer = new byte[512];
                    
                    for (int read = inStream.read(buffer); read >= 0; read = inStream.read(buffer))
                        outStream.write(buffer, 0, read);
                    
                    inStream.close();
                    outStream.close();
                    
                    
                  //Sleeping for one second
                    System.out.println("1 second sleep");
                    try {
                    	  Thread.sleep(1000);
                    	} catch (InterruptedException ie) {
                    	}   
                    	
                    
                	} 
                finally 
                	{
                    socket.close();
                    System.exit(0);
                	}
            }
        }
        finally {
            listener.close();
        }
    }
    
    
    public static long _GetFileSize(String fileName)
    {
    	//System.out.println("In the _GetFileSize function");
    	//System.out.println("Trying to open: " + fileName); 
    	File file = new File(fileName);
    	
    	return file.length();  		
    }
    
    
    public static void _OpenFile( String fileName)
    {
    	//System.out.println("In the _OpenFile function");
    //System.out.println("Trying to open: " + fileName);    	
    	
    	File file = new File(fileName);
        FileInputStream fis = null;
        BufferedInputStream bis = null;
        DataInputStream dis = null;

        
        System.out.println("File Size is: " + file.length() + " Bytes");
        
        try {
          fis = new FileInputStream(file);

          // Here BufferedInputStream is added for fast reading.
          bis = new BufferedInputStream(fis);
          dis = new DataInputStream(bis);

          // dis.available() returns 0 if the file does not have more lines.
          while (dis.available() != 0) {

          // this statement reads the line from the file and print it to
            // the console.
            System.out.println(dis.readLine());
          }

          // dispose all the resources after using them.
          fis.close();
          bis.close();
          dis.close();

        } catch (FileNotFoundException e) {
          e.printStackTrace();
          System.exit(0);
        } catch (IOException e) {
          e.printStackTrace();
          System.exit(0);
        }
    	System.out.print("\n\n\n");
    }
    
}