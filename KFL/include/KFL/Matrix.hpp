/**
 * @file Matrix.hpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#ifndef _KFL_MATRIX_HPP
#define _KFL_MATRIX_HPP

#include <boost/operators.hpp>

#include <KFL/Vector.hpp>

#pragma once

namespace KlayGE
{
	// 4D ����
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class Matrix4_T : boost::addable<Matrix4_T<T>,
						boost::subtractable<Matrix4_T<T>,
						boost::dividable2<Matrix4_T<T>, T,
						boost::multipliable2<Matrix4_T<T>, T,
						boost::equality_comparable<Matrix4_T<T> > > > > >
	{
		template <typename U>
		friend class Matrix4_T;

	public:
		typedef T					value_type;

		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;

		typedef value_type&			reference;
		typedef value_type const &	const_reference;

		typedef value_type*			iterator;
		typedef value_type const *	const_iterator;

		enum { row_num = 4, col_num = 4 };
		enum { elem_num = row_num * col_num };

	public:
		Matrix4_T()
			{ }
		explicit Matrix4_T(T const * rhs)
		{
			for (size_t i = 0; i < row_num; ++ i)
			{
				m_[i] = Vector_T<T, col_num>(rhs);
				rhs += col_num;
			}
		}
		Matrix4_T(Matrix4_T const & rhs)
			: m_(rhs.m_)
			{ }
		template <typename U>
		Matrix4_T(Matrix4_T<U> const & rhs)
			: m_(rhs.m_)
			{ }
		Matrix4_T(T const & f11, T const & f12, T const & f13, T const & f14,
			T const & f21, T const & f22, T const & f23, T const & f24,
			T const & f31, T const & f32, T const & f33, T const & f34,
			T const & f41, T const & f42, T const & f43, T const & f44)
		{
			m_[0][0] = f11;	m_[0][1] = f12;	m_[0][2] = f13;	m_[0][3] = f14;
			m_[1][0] = f21;	m_[1][1] = f22;	m_[1][2] = f23;	m_[1][3] = f24;
			m_[2][0] = f31;	m_[2][1] = f32;	m_[2][2] = f33;	m_[2][3] = f34;
			m_[3][0] = f41;	m_[3][1] = f42;	m_[3][2] = f43;	m_[3][3] = f44;
		}

		static size_t size()
			{ return elem_num; }

		static Matrix4_T const & Zero()
		{
			static Matrix4_T out(
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0);
			return out;
		}

		static Matrix4_T const & Identity()
		{
			static Matrix4_T out(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
			return out;
		}

		reference operator()(size_t row, size_t col)
			{ return m_[row][col]; }
		const_reference operator()(size_t row, size_t col) const
			{ return m_[row][col]; }
		iterator begin()
			{ return &m_[0][0]; }
		const_iterator begin() const
			{ return &m_[0][0]; }
		iterator end()
			{ return this->begin() + elem_num; }
		const_iterator end() const
			{ return this->begin() + elem_num; }
		reference operator[](size_t index)
			{ return *(this->begin() + index); }
		const_reference operator[](size_t index) const
			{ return *(this->begin() + index); }

		void Row(size_t index, Vector_T<T, col_num> const & rhs)
			{ m_[index] = rhs; }
		Vector_T<T, col_num> const & Row(size_t index) const
			{ return m_[index]; }
		void Col(size_t index, Vector_T<T, row_num> const & rhs)
		{
			for (size_t i = 0; i < row_num; ++ i)
			{
				m_[i][index] = rhs[i];
			}
		}
		Vector_T<T, row_num> const Col(size_t index) const
		{
			Vector_T<T, row_num> ret;
			for (size_t i = 0; i < row_num; ++ i)
			{
				ret[i] = m_[i][index];
			}
			return ret;
		}

		// ��ֵ������
		template <typename U>
		Matrix4_T& operator+=(Matrix4_T<U> const & rhs)
		{
			m_ += rhs.m_;
			return *this;
		}
		template <typename U>
		Matrix4_T& operator-=(Matrix4_T<U> const & rhs)
		{
			m_ -= rhs.m_;
			return *this;
		}
		template <typename U>
		Matrix4_T& operator*=(Matrix4_T<U> const & rhs)
		{
			*this = MathLib::mul(*this, rhs);
			return *this;
		}
		template <typename U>
		Matrix4_T& operator*=(U const & rhs)
		{
			for (size_t i = 0; i < row_num; ++ i)
			{
				m_[i] *= rhs;
			}
			return *this;
		}
		template <typename U>
		Matrix4_T& operator/=(U const & rhs)
			{ return this->operator*=(1.0f / rhs); }

		Matrix4_T& operator=(Matrix4_T const & rhs)
		{
			if (this != &rhs)
			{
				m_ = rhs.m_;
			}
			return *this;
		}
		template <typename U>
		Matrix4_T& operator=(Matrix4_T<U> const & rhs)
		{
			if (this != &rhs)
			{
				m_ = rhs.m_;
			}
			return *this;
		}

		// һԪ������
		Matrix4_T const operator+() const
			{ return *this; }
		Matrix4_T const operator-() const
		{
			Matrix4_T temp(*this);
			temp.m_ = -m_;
			return temp;
		}

		friend bool
		operator==(Matrix4_T const & lhs, Matrix4_T const & rhs)
		{
			return lhs.m_ == rhs.m_;
		}

	private:
		Vector_T<Vector_T<T, col_num>, row_num> m_;
	};

	template <typename T>
	inline Matrix4_T<T> const
	operator*(Matrix4_T<T> const & lhs, Matrix4_T<T> const & rhs)
	{
		return Matrix4_T<T>(lhs) *= rhs;
	}
}

#endif			// _KFL_MATRIX_HPP