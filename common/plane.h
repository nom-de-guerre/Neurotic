/*

Copyright (c) 2020, Douglas Santry
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, is permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef __DJS_PLANE__H__
#define __DJS_PLANE__H__

/*
 * IMPORTANT: This data structure employs row oriented storage.
 *
 */

class plane_t
{
	bool		dd_releaseMemory;
	int			dd_rows;
	int			dd_columns;
	double		*dd_datap;

public:

	plane_t (void) :
		dd_releaseMemory (false),
		dd_rows (-1),
		dd_columns (-1),
		dd_datap (NULL)
	{
	}

	plane_t (const int rows, const int columns) :
		dd_releaseMemory (true),
		dd_rows (rows),
		dd_columns (columns),
		dd_datap (new double [rows * columns])
	{
	}

	plane_t (const int rows, const int columns, double *datap) :
		dd_releaseMemory (false),
		dd_rows (rows),
		dd_columns (columns),
		dd_datap (datap)
	{
	}

	plane_t (const plane_t &Z) :
		dd_releaseMemory (true),
		dd_rows (Z.rows ()),
		dd_columns (Z.columns ()),
		dd_datap (new double [dd_rows * dd_columns])
	{
		memcpy (dd_datap, Z.raw (), sizeof (double) * N ());
	}

	~plane_t (void)
	{
		if (dd_releaseMemory && dd_datap)
			delete [] dd_datap;
	}

	void Reset (void)
	{
		memset (dd_datap, 0, sizeof (double) * N ());
	}

	int rows (void) const
	{
		return dd_rows;
	}

	int columns (void) const
	{
		return dd_columns;
	}

	int N (void) const
	{
		return dd_rows * dd_columns;
	}

	int stride (void) const
	{
		return dd_columns;
	}

	double *raw (void) const
	{
		return dd_datap;
	}

	double *raw (int row, int column) const
	{
		return dd_datap + (row * dd_columns) + column;
	}

	void setRaw (double *datap)
	{
		dd_releaseMemory = false;
		dd_datap = datap;
	}

	double &operator() (int row, int column) const
	{
		return dd_datap[(row * dd_columns) + column];
	}

	void display (const char * = NULL);
	void displayImage (const char * = NULL);
};

void plane_t::display (const char *msgp)
{
	printf ("%d\t%d\t", dd_rows, dd_columns);
	if (msgp)
		printf ("%s\n", msgp);

	printf ("\n");

	for (int i = 0, index = 0; i < dd_rows; ++i)
	{
		for (int j = 0; j < dd_columns; ++j, ++index)
			printf ("%f ", dd_datap[index]);

		printf ("\n");
	}
}

void plane_t::displayImage (const char *msgp)
{
	if (msgp)
		printf ("%s\n", msgp);

	for (int i = 0, index = 0; i < dd_rows; ++i)
	{
		for (int j = 0; j < dd_columns; ++j, ++index)
		{
			if (dd_datap[index] < -0.25)
				printf ("%c", ' ');
			else if (dd_datap[index] < 0.0)
				printf ("%c", '.');
			else if (dd_datap[index] < 0.25)
				printf ("%c", '+');
			else
				printf ("%c", '*');
		}

		printf ("\n");
	}
}

#endif // header inclusion

