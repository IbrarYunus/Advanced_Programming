import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.util.StringTokenizer;

import javax.swing.JOptionPane;

/**
 * 
 * @IBRAR YUNUS
 *   BSCS-2B
 *   HTTP 1.1 Server
 */

public class Server {
	static String Basic = "NULL";
	static int HEADbit = 0;
	static int POSTbit = 0;
	
    /**
     * Runs the server.
     */
    public static void main(String[] args) throws IOException 
    {
    	//Variables
    	long size;
   
    	
    	System.out.println("Server Intialized\n");
    	System.out.println("Grabbing a Socket");
    	
    	//Starts a listener on socket 2222
    	ServerSocket listener = new ServerSocket(2221);
        try {
            while (true) 
            {
            	System.out.println("Listener Initiated");
            	//If a connection is accepted
                Socket socket = listener.accept();
                System.out.println("Connection Accepted\n\n");
                try {
                	
                	//New input stream initialized to take messages from the web-browser
                	BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                	String requestedFile;
                	///Ignore this
                	String temp = "A";
                	
                	int count = 0;
                	
                	//For reading the whole message from the web-browser
                	while (temp != null && !temp.isEmpty())
                	{
                	temp = 	in.readLine();
                	
                	if(count == 0)
                	{
                		Basic = temp;
                		count = 1;
                	}
                	System.out.println(temp); 

                	}
                	
                	// Basic stores the first line of the HTTP Request 
                	System.out.println("Basic is: " + Basic);
	
                	//for debugging
                	StringTokenizer defaultTokenizer = new StringTokenizer(Basic);
                	System.out.println("Total number of tokens found : " + defaultTokenizer.countTokens());         	               	
                	requestedFile = defaultTokenizer.nextToken();
                	requestedFile =  defaultTokenizer.nextToken();

                	//Identifies a GET, POST or HEAD method
                	basicHandler(Basic);
                	
                	//To extract path from the HTTP 1.1 request
                	String[] tokens = requestedFile.split("/");
                	//To send messages to the web-browser
                	DataOutputStream toSend = new DataOutputStream(socket.getOutputStream());
                	
                	//If no path is given in the Request
                	if(tokens.length == 0)
                	{
                		System.out.println("SENDING OKAY");                		
                		toSend.writeBytes(sendOK());
                	}
                	
                	//If a path is given, then
                	else
                	{
                		System.out.println("Parsing for files: ");
                	    String fileName = tokens[1];
                	    System.out.println("Path is: " + fileName +"");
                	    File file = new File(fileName);
                	    
                	    //If the user tries to access Admin, then 
                		if (fileName.compareTo("admin") == 0)
                    	{
                    		System.out.println("Forbidden Resource!!");
                    		toSend.writeBytes(send401());
                    	}
                		
                		//If the user tries to access Oldindex
                		else if (fileName.compareTo("oldindex") == 0)
                    	{
                    		System.out.println("Moved Permanently!!");
                    		toSend.writeBytes(send301());
                    	}
                		
                		//If a resource does not exist
                	    else if(!file.exists())              	    
                    	{
                    		System.out.println("File is NOT found!!");
                    		toSend.writeBytes(send404());                    		
                    	}
                    	
                		//If a resource exits, then send that resource
                    	else
                    	{
                    		System.out.println("Try to Send  File");
                    		toSend.writeBytes(sendFile(fileName));
                    	}
                	}                                  	
                	
                	} 
                finally 
                	{
                    socket.close();
                	}
            }
        }
        finally {
            listener.close();
        }
    }
    
 ////////END OF MAIN   
 ////////////////////////   
    
    public static String sendOK()
    {
    	
		String  outputdata ="HTTP/1.1 200 OK\n" + "Content-Type: text/html\n" + "HTTP/1.1 200 OK\n"
		 				+ "Content-Type: text/html\n" + "Content-Length: ";
		String msg = "201 - OK!";					
		outputdata = outputdata + msg.length();
		outputdata = outputdata + "\n\n" + msg;
		

		return outputdata;
    }
    
    public static String send404()
    {
 
		String  outputdata ="HTTP/1.1 404 Not Found\n" + "Content-Type: text/html\n" + "Content-Length: ";
		String msg = "404 - Resource Not Found!";					
		outputdata = outputdata + msg.length();
		outputdata = outputdata + "\n\n" + msg;
		

		return outputdata;
    }
    
    public static String send401()
    {

		String  outputdata ="HTTP/1.1 401 Unauthorized\n" + "Content-Type: text/html\n" + "Content-Length: ";
		String msg = "401 - Unauthorized!";					
		outputdata = outputdata + msg.length();
		outputdata = outputdata + "\n\n" + msg;
		
		return outputdata;
    }
    
    
    public static String send301()
    {

		String  outputdata ="HTTP/1.1 301 Moved Permanently\n" + "Content-Type: text/html\n" + "Content-Length: ";
		String msg = "301 - Moved Permanently!";					
		outputdata = outputdata + msg.length();
		outputdata = outputdata + "\n\n" + msg;
		
		return outputdata;
    }
    
    public static String sendFile(String fileName) throws IOException
    {
    	//System.out.println("\n\n\n Testing\n");
		String  outputdata ="HTTP/1.1 200 OK\n" + "Content-Type: text/html\n" + "Content-Length: ";
		
		String msg = readFile(fileName);					
		outputdata = outputdata + msg.length();
		
		if(HEADbit == 0)
			outputdata = outputdata + "\n\n" + msg;
		
		return outputdata;
		
    }
    
    
    public static String readFile(String fileName) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        try {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append("\n");
                line = br.readLine();
            }
            return sb.toString();
        } finally {
            br.close();
        }
    }
    
    public static void basicHandler(String Request)
    {
    	StringTokenizer defaultTokenizer = new StringTokenizer(Request);
    	String Method = defaultTokenizer.nextToken();
    	
    	if(Method.compareTo("HEAD") == 0)
    	{
    		HEADbit = 1;
    	}
    	if(Method.compareTo("POST") == 0)
    	{
    		POSTbit = 1;
    	}
    	
    }
    
    
    
    
    
    

}