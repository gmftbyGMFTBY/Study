import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.IOException;

public class test{
    public static void main(String[] args) {
        int[][] A = read_file("../../data/matrix_a");
        int[][] B = read_file("../../data/matrix_b");
        // define the size of the matrix
        int n = 200;
        int m = 200;
        int p = 200;
        int[][] C = new int[m][p];
        
        multiply_matrix(A, B, C, m, p, n);
        
        /*
        for(int i = 0;i < m;i++)
        {
           for(int j = 0;j < p;j++) System.out.print(C[i][j]+"\t");
           System.out.println();
        }
        */
    }

    // read the file and return the matrix
    public static int[][] read_file(String path)
    {
        // read the file
        // init the matrix for reading the file
        int[][] rows = new int[200][200];
        int index = 0;
        BufferedReader br = null;
        try {
            // read the file from the path
            br  = new BufferedReader(new FileReader(new File(path)));
            String str = null;
            // the row 
            while((str = br.readLine()) != null) {
                // split by space, `index` is the index for the matrix in the row
                String[] string_rows = str.split("( )+");
                // parser into int
                for(int i = 0; i < string_rows.length; i++)
                {
                    rows[index][i] = Integer.parseInt(string_rows[i]);
                }
                index++;
            }
            // show the result, right
            /*
            for (int[] datas : rows) {
                for (int data : datas) {
                    System.out.println(data);
                }
            }
            */

        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return rows;
    }

    // mulity matrix
    private static void multiply_matrix(int[][] a, int[][] b, int[][] c, int m, int p, int n) {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<p;j++)
            {
                c[i][j] = add(a[i],b,j,n);
            }
        }
    }
    // add
    private static int add(int[] a, int[][] b, int j, int n) {
        int sum=0;
        for(int k=0;k<n;k++)
        {
            sum+=a[k]*b[k][j];
        }
        return sum;
    }
    
}
