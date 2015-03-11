import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class UnitTest {
	public static String temp;
public static void main(String[] args) 
	{
	System.out.println("UnitTests");
	String []tests = new String[8];
	tests[0] = "http://localhost:2221";
	tests[1] = "http://localhost:2221/oldindex";
	tests[2] = "http://localhost:2221/cannotfind.html";
	tests[3] = "http://localhost:2221/admin";
	tests[4] = "http://localhost:2221/index.html";
	
	for(int i=0; i<5;i++ )
	{
	
	try {
		System.out.println("\nTEST: " + (i+1) + "> Request: " + tests[i]);
		URL url = new URL(tests[i]);
		
		HttpURLConnection connection = (HttpURLConnection) url.openConnection();
		connection.setRequestMethod("GET");
		connection.setUseCaches(false);
		connection.setDoOutput(true);
		connection.setDoInput(true);
		String temp = "";
		byte[] bytes = temp.getBytes();
		connection.setRequestProperty("ConteSystem.exit(1);nt-length", String.valueOf(bytes.length));
		connection.setRequestProperty("Content-type", "text/html");
		OutputStream out = connection.getOutputStream();
		out.write(bytes);
		out.flush();
		BufferedReader input = new BufferedReader(new InputStreamReader(connection.getInputStream()));
		
		while((temp = input.readLine()) != null)
		System.out.println(temp);
		out.close();
		input.close();
		connection.disconnect();
	} catch(Exception FileNotFoundException) 
	{
		if(i==2)
		System.out.println("404 - Resource Not Found!");
		if(i==3)
			System.out.println("401 - Unauthorized!");
	}
	}
	}
}