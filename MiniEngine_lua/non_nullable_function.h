#pragma once
#include <functional>
#include "template_helpers.h"
#include "fexception.h"

#ifndef NON_NULLABLE_FUNCTION_H
#define NON_NULLABLE_FUNCTION_H


namespace framework {


	template<int I_num, typename T_type>
	struct param_n;
	
	template<typename T_type> struct param_n<0, T_type> { using argument_0_type = T_type; };
	template<typename T_type> struct param_n<1, T_type> { using argument_1_type = T_type; };
	template<typename T_type> struct param_n<2, T_type> { using argument_2_type = T_type; };
	template<typename T_type> struct param_n<3, T_type> { using argument_3_type = T_type; };
	template<typename T_type> struct param_n<4, T_type> { using argument_4_type = T_type; };
	template<typename T_type> struct param_n<5, T_type> { using argument_5_type = T_type; };
	template<typename T_type> struct param_n<6, T_type> { using argument_6_type = T_type; };
	template<typename T_type> struct param_n<7, T_type> { using argument_7_type = T_type; };
	template<typename T_type> struct param_n<8, T_type> { using argument_8_type = T_type; };
	template<typename T_type> struct param_n<9, T_type> { using argument_9_type = T_type; };
	
	


	template<typename T_return_type, typename...T_param_types>
	class non_nullable_function : public inherit_for_each_arg<param_n, template_arg_pack<T_param_types...>>
	{
	public:

		using return_type = T_return_type;
		using function_type = std::function<T_return_type(T_param_types...)>;
		using argument_pack = template_arg_pack<T_param_types...>;

		non_nullable_function() = delete;
		non_nullable_function(std::function<T_return_type(T_param_types...)> func) : m_function{ func } {
			if (!func) {
				throw NULL_exception{};
			}
		}
		~non_nullable_function() = default;

		T_return_type operator()(T_param_types... params) { return m_function(params...); }

		void set(std::function<T_return_type(T_param_types...)> func) { 
			if (!func) {
				throw NULL_exception{};
			}
			m_function = func; 
		}

	private:
		std::function<T_return_type(T_param_types...)> m_function;
	};




	template<typename T_return_type>
	class non_nullable_function<T_return_type>
	{
	public:

		using return_type = T_return_type;
		using function_type = std::function<T_return_type()>;
		using argument_pack = template_arg_pack<>;

		non_nullable_function() = delete;
		non_nullable_function(std::function<T_return_type()> func) : m_function{ func } {
			if (!func) {
				throw NULL_exception{};
			}
		};
		~non_nullable_function() = default;

		T_return_type operator()() { return m_function(); }

		void set(std::function<T_return_type()> func) { 
			if (!func) {
				throw NULL_exception{};
			}
			m_function = func; 
		}

	private:
		std::function<T_return_type()> m_function;
	};


}


#endif // !NON_NULLABLE_FUNCTION_H