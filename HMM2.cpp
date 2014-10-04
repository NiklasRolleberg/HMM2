#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream> 

struct matrix 
{
	int row;
	int col;
	double** m;
	
	//constructor
	matrix(double** mat, int rows, int cols)
	{
		row = rows;
		col = cols;
		m = mat;
	}
	
	//constructor 2
	matrix(std::string in)
	{
		std::istringstream iss;
		iss.str(in);
		iss >> row >> col;
		
		m = (double**)calloc(row , sizeof(double *));
		for(int i=0 ; i< row ; ++i)
			m[i] = (double*)calloc(col , sizeof(double));
		
		for(int i=0;i<row;++i)
		{
			for(int j=0;j<col;++j)
			iss >> m[i][j];
		}
	}
	
	double get(int r, int c)
	{
		return m[r][c];
	}
	
	void print() 
	{
		for (int i=0;i<row;++i)
		{
			for(int j=0;j<col;++j)
				std::cout << m[i][j] <<" ";
			std::cout << std::endl;
		}		
	}
	
	void writeMatrix()
	{
		std::cout << row << " " << col;
		for(int i=0;i<row;++i) {
			for(int j=0; j<col;++j)
				std::cout << " " << m[i][j];
		}
	}
	
	void transpose()
	{
		int i,j;
		double* temp;
		for (i = 0; i < row/2; ++i) 
		{
			temp = m[row-i-1];
			m[row-i-1] = m[i];
			m[i] = temp;
			
			double temp2;
			
			for (j = 0; j < col/2; ++j) 
			{
				temp2 = m[i][col-i-1];
				m[i][row-i-1] = m[i][j];
				m[i][j] = temp2;
			}
			
			for (j = 0; j < col/2; ++j) 
			{
				temp2 = temp[col-i-1];
				temp[row-i-1] = temp[j];
				temp[j] = temp2;
			}

			m[i] = temp;
		}
		int a = col;
		row = col;
		col = a;
	}
	
	matrix getCol(int index)
	{
		int newRows = row;
		int newCols = 1;

		double** temp;
		temp = (double**)calloc(newRows , sizeof(double *));
		for(int i=0 ; i< newRows ; ++i)
			temp[i] = (double*)calloc(newCols , sizeof(double));
			
		for(int i=0;i<newRows;++i)
			temp[i][0] = m[i][index];
		return matrix(temp,newRows,newCols);
	}
	
	matrix operator*(matrix H)
	{
		int newRows = row;
		int newCols = H.col;
		
		if(col != H.row)
			std::cerr << "Fel. matrix 1: " << row << " " << col << ", matrix 2: " << H.row << " " << H.col << std::endl;

		double** temp;
		temp = (double**)calloc(newRows , sizeof(double *));
		for(int i=0 ; i< newRows ; ++i)
			temp[i] = (double*)calloc(newCols , sizeof(double));
		
		//RÄKNA!
		double t;
		int i,j,k;
		for (i=0;i<newRows;++i)
		{
			for(j=0;j<newCols;++j)
			{
				t = 0;
				//row in first matrix X col in second matrix;
				for(k=0;k<col;++k)
					t+= (m[i][k] * H.get(k,j));
				temp[i][j] = t;
			}
		}
		return matrix(temp,newRows,newCols);
	}

	matrix operator/(matrix H) // element multiplication
	{
		int newRows = row;
		int newCols = col;
		
		if(row!=H.row || col != H.col)
			std::cout << "FEL" << row << " " << H.row << " , " << col << H.col <<std::endl;

		double** temp;
		temp = (double**)calloc(newRows , sizeof(double *));
		for(int i=0 ; i< newRows ; ++i)
			temp[i] = (double*)calloc(newCols , sizeof(double));
		
		//RÄKNA!
		double t;
		int i,j,k;
		for (i=0;i<newRows;++i)
		{
			for(j=0;j<newCols;++j)
				temp[i][j] = m[i][j]*H.get(i,j);
		}
		return matrix(temp,newRows,newCols);
	}
	
};

int main(int argc, char **argv)
{
	// Read the file	
	std::vector<std::string> board;
	for (std::string line; std::getline(std::cin, line);)
		board.push_back(line);
		
	matrix A = matrix(board[0]);
	matrix B = matrix(board[1]);
	matrix q = matrix(board[2]);
		
	//
	std::cout <<" innan " << std::endl;
	A.print();
	std::cout <<" efter " << std::endl;
	A.transpose();
	//
	
	//find out the statesequence
	int Nstates;
	int index;
	std::istringstream iss;
	iss.str(board[3]);
	iss >> Nstates;
	iss >> index;
	
	matrix L = q/B.getCol(index); 
	L.print();
	for(int i=1;i<Nstates;++i)
	{
		iss >> index;
		std::cout << index << std::endl;
		matrix T = B.getCol(index);
		L = (L*A)/T;
		L.print();
	}
	
	//matrix P = q*A;
	//matrix Po = P*B;
	//Po.writeMatrix();
	return 0;
}

