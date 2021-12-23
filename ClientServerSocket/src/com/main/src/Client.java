/* 16290125 K. Eylul Sengun
 * 16290085 Y. Tugba Cetin
 * COM334 LAB3 - Client.java
 * This file creates client for sending the date provided by user's input to the Client.
*/
package com.main.src;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Client {
	public static void main(String[] args) throws UnknownHostException, IOException {
		
		String receiveMessage, outputDate;  
		String month, day, year;
			//creates Client socket in host: 127.0.0.1 on port: 5000
		Socket clientSocket = new Socket("127.0.0.1", 5000);
		
        System.out.println("Client is ready for the connection on port: " + clientSocket.getPort() + "\nPlease enter month, day and year...");
		
			//gets input from keyboard
        BufferedReader getInput = new BufferedReader(new InputStreamReader(System.in));
        
        	//sends the outputs of getInput to the server
        OutputStream ostream = clientSocket.getOutputStream(); 
        PrintWriter writeToServer = new PrintWriter(ostream, true);

    		//recieves date from server
        InputStream istream = clientSocket.getInputStream();
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));
        
        /*
         * Exception handling provides terminating and closing the client and server properly.
         * User input is month, day and year. Client takes them as string and combines them under the string outputDate.
         * The Client sends this string to the server for getting the expected output.
         * */
        
        try 
        { 
			while(true)
			{
				System.out.print("Month: ");
				month = getInput.readLine();
				System.out.print("Day: ");
				day = getInput.readLine();
				System.out.print("Year: ");
				year = getInput.readLine();			
				
					outputDate = month + "/" + day + "/" + year;
					
					writeToServer.println(outputDate);       // sends the date provided by user as string to the Server
					writeToServer.flush();                   // flush the data
					System.out.println("The date provided by you is: " + outputDate);
					
					receiveMessage = receiveRead.readLine();
					
					if(receiveMessage != null) //receive the difference from the Server
					{
						System.out.println("The difference between current time and your input is: ");
						System.out.println(receiveMessage); // displaying at DOS prompt
						System.out.println("Your operation is completed. Now, you can submit another date: \n");
					}
					//clears the value of date
					month = null; day = null; year = null;
			}
        }  	catch (IOException e) 
        	{
	            if (clientSocket != null && !clientSocket.isClosed()) {
	                try 
	                {
	                	clientSocket.close();
	                }  catch (IOException ex)
		               {
		                    ex.printStackTrace(System.err);
		               }
	            }
        	}
    } 
}