#pragma once

namespace engine {
	namespace math {
		class Fraction {
		// DEPRECATED, Using fixed point instead
		// This class assumes you're a competent programmer and will take care of things like overflows, division by 0, etc
		private:
			static const int min_int;
			static const int max_int; 

		public:
			int top_m;
			int bottom_m;

		public:
			Fraction(const int top = 0, const int bottom = 1);
			Fraction(const Fraction& other);
			~Fraction();

		public:
			// Operators
			const Fraction operator+(const Fraction &other) const;
			const Fraction operator+(const int number) const;
			friend const Fraction operator+(const int number, const Fraction &other);

			const Fraction operator-(const Fraction &other) const;
			const Fraction operator-(const int number) const;
			friend const Fraction operator-(const int number, const Fraction &other);

			const Fraction operator*(const Fraction &other) const;
			const Fraction operator*(const int number) const;
			friend const Fraction operator*(const int number, const Fraction &other);

			const Fraction operator/(const Fraction &other) const;
			const Fraction operator/(const int number) const;
			friend const Fraction operator/(const int number, const Fraction &other);

			Fraction& operator=(const Fraction &other);
			Fraction& operator=(const int number);

			Fraction& operator+=(const Fraction &other);
			Fraction& operator+=(const int number);

			Fraction& operator-=(const Fraction &other);
			Fraction& operator-=(const int number);

			Fraction& operator*=(const Fraction &other);
			Fraction& operator*=(const int number);

			Fraction& operator/=(const Fraction &other);
			Fraction& operator/=(const int number);

			// Logical operators
			bool operator==(const Fraction &other) const;
			bool operator==(const int number) const;
			friend bool operator==(const int number, const Fraction &other);

			bool operator!=(const Fraction &other) const;
			bool operator!=(const int number) const;
			friend bool operator!=(const int number, const Fraction &other);

			bool operator<(const Fraction &other) const;
			bool operator<(const int number) const;
			friend bool operator<(const int number, const Fraction &other);

			bool operator>(const Fraction &other) const;
			bool operator>(const int number) const;
			friend bool operator>(const int number, const Fraction &other);

			bool operator<=(const Fraction &other) const;
			bool operator<=(const int number) const;
			friend bool operator<=(const int number, const Fraction &other);

			bool operator>=(const Fraction &other) const;
			bool operator>=(const int number) const;
			friend bool operator>=(const int number, const Fraction &other);

			// Methods
			int to_int() const;
			void prevent_overflow();
			const Fraction abs() const;
		};
	}  // namespace math
}  // namespace engine