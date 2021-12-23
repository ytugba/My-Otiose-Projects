/* 16290085 Y. Tugba Cetin
 * 16290125 K. Eylul Sengun
 * COM334 LAB3 - Server.java
 * This file creates server for calculating the difference between current date and the date sent by client.
 * Output format is: Month/Day/Year
 * Leap year error is minimized.
*/
package com.main.src;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Server 
{
	public static void main(String[] args) throws IOException, ParseException 
	{		
        long currentDate = System.currentTimeMillis(); //current time provided by server in miliseconds   
        String recievedInput = null;
        long difference = 0;
        int month = 0 , day = 0 , year = 0 , totalDays = 0;
		Date date = new Date(currentDate);
			//create server socket and bound it to the port 5000 and ready to run with client socket
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server is ready for the connection...\nPlease run the Client...");    
        Socket clientSocket = serverSocket.accept();
        
        SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("MM/dd/yyyy");
        
        	//sends the outputs to the client
        OutputStream ostream = clientSocket.getOutputStream(); 
        PrintWriter writeToClient = new PrintWriter(ostream, true);
        
        	//recieves date from client
        InputStream istream = clientSocket.getInputStream();
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(istream));
        
        /* Respectively month, day and year are taken from the user as string. Then, we converted the string to Date.
         * The difference is the result of substraction of current date and input date in miliseconds.
         * 30.416 and double casting are for minimizing the error caused by leap years.
         * It sends the converted result to the client back. 
         */
        
        try 
        { 
	        while(true)
	        {
	        	if((recievedInput = receiveRead.readLine()) != null)  
	        	{
		        	  Date input_Date = DATE_FORMAT.parse(recievedInput);
		              
		        	  difference = currentDate - input_Date.getTime();
		              
		        	  totalDays = Math.abs((int) (difference / (1000*60*60*24))) ;
		              year = Math.abs(totalDays / 365);
		              
		              if(totalDays > 1095)
		              {
		            	  month =Math.abs( (int) ( (int) ((int) (totalDays + (int)(year / 4)) / 30.4465) %12));
		              }
		              else
		              {
		            	  month =Math.abs( (int) ( (int) ((int)(totalDays + (int)(year / 4)) / 30.4) %12));
		              }
		              		             
		              day = Math.abs(((int) (totalDays % 365) - (int)(year / 4)));
		             
		              if(day >= 31)
		              {
		            	  day = Math.abs( (int) (( (int) (totalDays % 365) - (int)(year / 4) ) % 30.1466667));
		              }		                      
		              System.out.println("The date provided by server is: " + DATE_FORMAT.format(date));
		              writeToClient.println(month + "/" + day + "/" + year); 
		              writeToClient.flush();  
	        	}
	        } 
        }  	catch (IOException e) 
        	{
	            if (serverSocket != null && !serverSocket.isClosed()) {
	                try 
	                {
	                	serverSocket.close();
	                }  	catch (IOException ex)
		                {
		                    ex.printStackTrace(System.err);
		                }
	            }
        	}
	}
}