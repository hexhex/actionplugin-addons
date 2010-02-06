//package sample.calendar;

import com.google.gdata.client.*;
import com.google.gdata.client.calendar.*;
import com.google.gdata.data.*;
import com.google.gdata.data.acl.*;
import com.google.gdata.data.calendar.*;
import com.google.gdata.data.extensions.*;
import com.google.gdata.util.*;

import java.net.*;
import java.io.*;

//import sample.util.*;




public class calendarApp {

    public static void main(String[] args) throws AuthenticationException, MalformedURLException, IOException, ServiceException{
        CalendarService myService = new CalendarService("exampleCo-exampleApp-1.0");
        myService.setUserCredentials(args[4], args[5]);          
  
        URL feedUrl = new URL("http://www.google.com/calendar/feeds/default/allcalendars/full");
        CalendarFeed resultFeed = myService.getFeed(feedUrl, CalendarFeed.class);
            
//        System.out.println("Your calendars:");
//        System.out.println();
        
        for (int i = 0; i < resultFeed.getEntries().size(); i++) {
          CalendarEntry entry = resultFeed.getEntries().get(i);
        //  System.out.println("\t" + entry.getTitle().getPlainText());

	//  System.out.println("arg0 is "+args[0] );
	  if(entry.getTitle().getPlainText().equals(args[0]))
	  {
		System.out.println("Inserting an entry to "+args[0]+ " calendar");

		EventEntry myEntry = new EventEntry();
		myEntry.setTitle(new PlainTextConstruct(args [2]));
		//myEntry.setContent(new PlainTextConstruct("Some explanation on entry"));

		//Person author = new Person("Elizabeth Bennet", null, "liz@gmail.com");
		//myEntry.getAuthors().add(author);
		String stime=args[3];
		stime=stime.substring(1, stime.length()-2);
		stime = stime+"+01:00";
		String endtime=stime;
		String temp[]=null;
		temp=endtime.split("T");
		int time_int=Integer.parseInt(temp[1].substring(0,2));
		time_int=time_int+1;
		temp[1]=Integer.toString(time_int)+temp[1].substring(2, temp[1].length());
		if(time_int<10)
		{
			temp[1]="0"+temp[1];
		}
		endtime=temp[0]+"T"+temp[1];
		DateTime startTime = DateTime.parseDateTime(stime);
		DateTime endTime = DateTime.parseDateTime(endtime);
		When eventTimes = new When();
		eventTimes.setStartTime(startTime);
		eventTimes.setEndTime(endTime);
		myEntry.addTime(eventTimes);

		// Send the request and receive the response:
		// URL postUrl =  new URL(entry.getHtmlLink().getHref());
		URL postUrl =  new URL(args[1]);
		EventEntry insertedEntry = myService.insert(postUrl, myEntry);
	  }	
        }

//	URL postUrl =  new URL("http://www.google.com/calendar/feeds/smile2903@gmail.com/private/full");
	
    
    }
}
