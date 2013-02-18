import java.io.InputStreamReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;
import java.io.InputStream;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.FileReader;


public class GenerateSH
{
	public static void main(String[] Args)throws IOException
	{
		String outputStream = "link.sh";
		String outputStream2 = "CodeRunner.sh";
		InputStream inputStream = System.in;
		PrintWriter out = new PrintWriter(outputStream);
		PrintWriter out2 = new PrintWriter(outputStream2);
		Generator generator = new Generator();
		generator.generate(1, out, out2);
		out.close();
		out2.close();
	}
}

class Generator
{
	public void generate(int testNumber, PrintWriter out, PrintWriter out2)throws IOException
	{
		String s="";
		String currentDir = System.getProperty("user.dir");
        System.out.println("Current dir: " +currentDir);
        s="echo \"CodeRunner Started\" >> "+currentDir+"/Logs/Logs2.txt \n "+currentDir+"/main -q >> "+currentDir+"/Logs/Logs2.txt";
        out.println(s);
        String s2="until "+currentDir+"/link.sh; do \n echo \" CodeRunner crashed with exit code $?.  Respawning.. \" >&2 \n sleep 1 \n done";
        out2.println(s2);
	}
}
