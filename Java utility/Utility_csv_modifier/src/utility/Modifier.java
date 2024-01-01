package utility;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;

public class Modifier {

	public static void main(String[] args) {
		
		String filename = "AVR161_Remote_Commands.csv";
		try {
			BufferedReader reader = new BufferedReader(new FileReader(filename ));
			String str = reader.readLine();
			String[]  cells = str.split(",");
			File file = new File("newFile.txt");
			PrintWriter writer = new PrintWriter(new FileWriter(file, true));
			Arrays.stream(cells).forEach(c -> writer.print(c.toString() + "\t"));
			Arrays.stream(cells).forEach(c -> System.out.print(c.toString() + "\t"));
			
			String type = "Command";
			while( str != null) {
				cells = str.split(",");
				cells[0] = cells[0].replaceAll("\"\"", "");
				String name = "key" + cells[0].replaceAll("(\"|/|\\*|-)", "");
				writer.print(type + " " + name + " = {" + cells[0] +", " + cells[1] + ", " + cells[2] + "};");
				writer.println();
				System.out.print(type + " " + name + " = {" + cells[0] +", " + cells[1] + ", " + cells[2] + "};");
				System.out.println();
				str = reader.readLine();
			}
			writer.close();
			
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
