/* Ibrar Yunus
 * 
 * BSCS-2B
 * REG- 1190
 * 
 */


/*Imports*/
import java.io.*;     
import java.util.*;   



/*The Spider Crawler Class*/
public abstract class SpiderCrawler implements Runnable{
	
    private volatile File param1;
    private volatile String param2;


	static List<IndexRecord> list = new ArrayList<IndexRecord>();
	static List<StringRecord> Stringlist = new ArrayList<StringRecord>();
	
	public SpiderCrawler(File param1, String param2)
	{
		this.param1 = param1;
		this.param2 = param2;		
	}
	
    public static void main(String[] args) throws IOException {
    	
    	/*Take directory from the user*/
        Scanner console = new Scanner(System.in);
        System.out.print("Directory? ");
        String directoryName = console.nextLine();
        
        /*Creates a File object to search in the file structure*/
        File f = new File(directoryName);
        
        /*the Crawl Function takes the File argument and starts the searching*/
        System.out.println("Populating Indexes");
        crawl(f);
        System.out.println("Total Files Found: " + list.size() );
        System.out.println("Select the Following Options: ");
        System.out.println("1. Search by File Name ");
        System.out.println("2. Search by File Content(txt) ");

        String Option = console.nextLine();
        
        if(Option.compareTo("1") == 0)
        {
        	System.out.println("File to Search?: ");
        	String fileName = console.nextLine();
            searchList(fileName);
        }
        if(Option.compareTo("2") == 0)
        {
            System.out.println("Enter Text Content?: ");
        	String TxtContent = console.nextLine();
        	searchStringlist(TxtContent);
        }
        
        //debuglist();
    }
    
    
    

    public static void crawl(File f) throws IOException {
    	run(f, "");
    }
    
  
    public static  void run(File f, String indent) throws IOException {
    	//System.out.println((f.length()/1024) + " MB" + indent + f.getAbsolutePath() + f.getName());
    	IndexRecord temp = null;
    	temp = new IndexRecord();
    	temp._fname = f.getName();
    	temp._fpath = f.getAbsolutePath();
    	temp._fsize = (int) ((f.length())/1024);
    	
    	if(f.getName().endsWith(".txt") && f.isFile())
    	{
    		int readlimiter = 0;
    		//System.out.println(f.getName() + " is a txt file");
    		FileInputStream in = new FileInputStream(f.getAbsoluteFile());
    	    BufferedReader br = new BufferedReader(new InputStreamReader(in));

    	    String strLine;

        	StringRecord temp2 = null;
        	temp2 = new StringRecord();
        	temp2._fname = f.getName();
        	temp2._fpath = f.getPath();
        	temp2._fstring = "";
    	    while ((strLine = br.readLine()) != null) {
    	    	readlimiter++;
    	    	temp2._fstring = temp2._fstring + strLine;
    	    	if(readlimiter > 200)
    	    		break;
    	    }
    	    in.close();
    	    Stringlist.add(temp2);
    	}
    	
    	
    	list.add(temp);
    	
    	if (f.isDirectory()) {
        	// recursive case: directory
        	// print everything in the directory
        	File[] subFiles = f.listFiles();
    		indent += "    ";
    		SpiderCrawler[] myRunnable = new SpiderCrawler[subFiles.length];  
    		
        	for (int i = 0; i < subFiles.length; i++) {
              	run(subFiles[i], indent);
        	}
        }
    }
    
    private static void debuglist()
    {
    	System.out.println("Debugging the LIST\n");
    	for (ListIterator<IndexRecord> iter = list.listIterator(); iter.hasNext(); ) {
    	    IndexRecord element = iter.next();
    	    System.out.println(element._fsize + "\n");
    	}
    }
    
    
    private static void searchStringlist(String TxtContent)
    {
    	int counter = 0;
    	System.out.println("Debugging the STRING LIST\n");
    	for (ListIterator<StringRecord> iter = Stringlist.listIterator(); iter.hasNext(); ) {
    	    StringRecord element = iter.next();
    	    if(element._fstring.contains(TxtContent))
    	    {
    	    	System.out.println("Text Found!");
    	    	System.out.println("At File: " + element._fpath);
    	    	counter = 1;
    	    	break;
    	    }
    	}
    	
    	if (counter == 0)
    		System.out.println("Could not find the specified text!");
    	//System.out.println(Stringlist.get(4));
    	
    }
    private static void searchList(String fileName)
    {
    	//System.out.println("Debugging the LIST\n");
    	int successfulFind = 0;
    	for (ListIterator<IndexRecord> iter = list.listIterator(); iter.hasNext(); ) {
    	    IndexRecord element = iter.next();
    	    if(element._fname.compareTo(fileName) == 0)
    	    {
    	    	System.out.println("File Found!");
    	    	System.out.println("at: " + element._fpath);
    	    	successfulFind = 1;
    	    }
    	}
    	if(successfulFind == 0)
    	{
    		System.out.println("No Files Found With That Name!");
    	}
    }    
}