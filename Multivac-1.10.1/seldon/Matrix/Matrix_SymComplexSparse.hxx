// Copyright (C) 2001-2004 Vivien Mallet
//
// This file is part of Seldon library.
// Seldon library provides matrices and vectors structures for
// linear algebra.
// 
// Seldon is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Seldon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (file "license") for more details.
//
// For more information, please see the Seldon home page:
//     http://spacetown.free.fr/lib/seldon/

// To be included by Seldon.hxx

#ifndef SELDON_FILE_MATRIX_SYMCOMPLEXSPARSE_HXX

#include "../Common/Common.hxx"
#include "../Common/Properties.hxx"
#include "../Common/Storage.hxx"
#include "../Common/Errors.cxx"
#include "../Common/Allocator.hxx"

namespace Seldon
{
  

  //! Symmetric complex sparse-matrix class.
  /*!
    Symmetric sparse matrices are defined by: (1) the number of rows
    and columns; (2) the number of non-zero entries; (3) an array 'ptr_' of
    start indices (i.e. indices of the first element of each row or column,
    depending on the storage); (4) an array 'ind_' of column or row indices
    of each non-zero entry; (5) values of non-zero entries.\par
    Complex sparse matrices are defined in the same way except that real
    and imaginary parts are splitted. It is as if two matrices were stored.
    There are therefore 6 arrays: 'real_ptr_', 'real_ind_', 'real_data_',
    'imag_ptr_', 'imag_ind_' and 'imag_data_'.\par
    Finally, since the matrix is symmetric, only its upper part is stored.
  */
  template <class T, class Prop, class Storage,
	    class Allocator = SELDON_DEFAULT_ALLOCATOR<T> >
  class Matrix_SymComplexSparse: public Spacetown,
				 public Matrix_Base<T, Allocator>
  {
    // typedef declaration.
  public:
    typedef typename Allocator::value_type value_type;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;

    // Attributes.
  protected:
    // Number of non-zero (stored) elements.
    int real_nz_;
    int imag_nz_;
    // Index (in data_) of first element stored for each row or column.
    int* real_ptr_;
    int* imag_ptr_;
    // Column or row index (in the matrix) each element.
    int* real_ind_;
    int* imag_ind_;

    // Data.
    T* real_data_;
    T* imag_data_;

    // Methods.
  public:
    // Constructors.
    Matrix_SymComplexSparse();
    Matrix_SymComplexSparse(int i, int j);
    Matrix_SymComplexSparse(int i, int j, int real_nz, int imag_nz);
    template <class Storage0, class Allocator0,
	      class Storage1, class Allocator1,
	      class Storage2, class Allocator2>
    Matrix_SymComplexSparse(int i, int j,
			    Vector<T, Storage0, Allocator0>& real_values,
			    Vector<int, Storage1, Allocator1>& real_ptr,
			    Vector<int, Storage2, Allocator2>& real_ind,
			    Vector<T, Storage0, Allocator0>& imag_values,
			    Vector<int, Storage1, Allocator1>& imag_ptr,
			    Vector<int, Storage2, Allocator2>& imag_ind);
    
    // Destructor.
    ~Matrix_SymComplexSparse();
    void Clear();

    // Memory management.
    template <class Storage0, class Allocator0,
	      class Storage1, class Allocator1,
	      class Storage2, class Allocator2>
    void SetData(int i, int j,
		 Vector<T, Storage0, Allocator0>& real_values,
		 Vector<int, Storage1, Allocator1>& real_ptr,
		 Vector<int, Storage2, Allocator2>& real_ind,
		 Vector<T, Storage0, Allocator0>& imag_values,
		 Vector<int, Storage1, Allocator1>& imag_ptr,
		 Vector<int, Storage2, Allocator2>& imag_ind);
    void SetData(int i, int j,
		 int real_nz, pointer real_values, int* real_ptr,
		 int* real_ind,
		 int imag_nz, pointer imag_values, int* imag_ptr,
		 int* imag_ind);

    // Basic methods.
    int GetNonZeros() const;
    int GetDataSize() const;
    int* GetRealPtr() const;
    int* GetImagPtr() const;
    int* GetRealInd() const;
    int* GetImagInd() const;
    int GetRealPtrSize() const;
    int GetImagPtrSize() const;
    int GetRealIndSize() const;
    int GetImagIndSize() const;
    T* GetRealData() const;
    T* GetImagData() const;

    // Element acess and affectation.
    complex<value_type> operator() (int i, int j) const;
    
    // Convenient functions.
    void Print() const;
  };


  //! Column-major complex sparse-matrix class.
  template <class T, class Prop, class Allocator>
  class Matrix<T, Prop, ColSymComplexSparse, Allocator>:
    public Matrix_SymComplexSparse<T, Prop, ColSymComplexSparse, Allocator>
  {
  public:
    Matrix()  throw();
    Matrix(int i, int j);
    Matrix(int i, int j, int real_nz, int imag_nz);
    template <class Storage0, class Allocator0,
	      class Storage1, class Allocator1,
	      class Storage2, class Allocator2>
    Matrix(int i, int j,
	   Vector<T, Storage0, Allocator0>& real_values,
	   Vector<int, Storage1, Allocator1>& real_ptr,
	   Vector<int, Storage2, Allocator2>& real_ind,
	   Vector<T, Storage0, Allocator0>& imag_values,
	   Vector<int, Storage1, Allocator1>& imag_ptr,
	   Vector<int, Storage2, Allocator2>& imag_ind);
  };


  //! Row-major complex sparse-matrix class.
  template <class T, class Prop, class Allocator>
  class Matrix<T, Prop, RowSymComplexSparse, Allocator>:
    public Matrix_SymComplexSparse<T, Prop, RowSymComplexSparse, Allocator>
  {
  public:
    Matrix()  throw();
    Matrix(int i, int j);
    Matrix(int i, int j, int real_nz, int imag_nz);
    template <class Storage0, class Allocator0,
	      class Storage1, class Allocator1,
	      class Storage2, class Allocator2>
    Matrix(int i, int j,
	   Vector<T, Storage0, Allocator0>& values,
	   Vector<int, Storage1, Allocator1>& ptr,
	   Vector<int, Storage2, Allocator2>& ind,
	   Vector<T, Storage0, Allocator0>& imag_values,
	   Vector<int, Storage1, Allocator1>& imag_ptr,
	   Vector<int, Storage2, Allocator2>& imag_ind);
  };


} // namespace Seldon.

#define SELDON_FILE_MATRIX_SYMCOMPLEXSPARSE_HXX
#endif
