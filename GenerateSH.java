
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Arrays;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;
import java.io.InputStream;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.FileReader;
import java.util.Scanner;


public class GenerateSH
{
	public static void main(String[] Args)throws IOException
	{
		long t1=System.currentTimeMillis();
		//String inputStream = "Input/1.txt";
		String outputStream = "CodeRunner.sh";
		InputStream inputStream = System.in;
		//OutputStream outputStream = System.out;
		Scanner in = new Scanner(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		//PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(outputStream)));
		Generator generator = new Generator();
		generator.generate(1, in, out);
		out.close();
		long t2=System.currentTimeMillis();
		System.out.println(t2-t1+"ms");
	}
}

class Generator
{
	public void generate(int testNumber, Scanner in, PrintWriter out)throws IOException
	{
		String s="";
		String currentDir = System.getProperty("user.dir");
        System.out.println("Current dir: " +currentDir);
        s="until "+currentDir+"/main -q; do \n echo \" CodeRunner crashed with exit code $?.  Respawning.. \" >&2 \n sleep 1 \n done";
        out.println(s);
	}
}
