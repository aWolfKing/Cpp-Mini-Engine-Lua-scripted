#pragma once
#ifndef TEMPLATE_HELPERS_H
#define TEMPLATE_HELPERS_H


/* Indicates 'no type'. */
struct template_null_type {};




template<typename... T_types>
/* A type that 'holds' an argument pack. */
struct template_arg_pack {};




template<typename T_to_add, typename... T_deduced>
/* Adds T_to_add to the front of arg_pack's arguments. */
constexpr auto Add_arg_to_front_of_pack(template_arg_pack<T_deduced...> arg_pack)->template_arg_pack<T_to_add, T_deduced...>;


template<typename T_to_add, typename... T_deduced>
/* Adds T_to_add to the end of arg_pack's arguments. */
constexpr auto Add_arg_to_end_of_pack(template_arg_pack<T_deduced...> arg_pack)->template_arg_pack<T_deduced..., T_to_add>;


template<typename T_begin, typename... T_deduced>
/* Adds T_to_add to the front of arg_pack's arguments. */
constexpr auto Remove_arg_from_front_of_pack(template_arg_pack<T_begin, T_deduced...> arg_pack)->template_arg_pack<T_deduced...>;


template<typename... T_deduced, typename T_end>
/* Adds T_to_add to the end of arg_pack's arguments. */
constexpr auto Remove_arg_from_end_of_pack(template_arg_pack<T_deduced..., T_end> arg_pack)->template_arg_pack<T_deduced...>;




namespace template_helpers {
	namespace impl {


		template<bool B_first, typename T_reversed_arg_pack, typename T_type, typename... T_tail>
		struct argument_reverser
		{
			using reversed_arguments = typename argument_reverser<false, decltype(Add_arg_to_front_of_pack<T_type>(T_reversed_arg_pack{})), T_tail...>::reversed_arguments;
		};


		template<typename T_reversed_arg_pack, typename T_type, typename... T_tail>
		struct argument_reverser<true, T_reversed_arg_pack, T_type, T_tail...>
		{
			using reversed_arguments = typename argument_reverser<false, template_arg_pack<T_type>, T_tail...>::reversed_arguments;
		};


		template<typename T_reversed_arg_pack, typename T_type>
		struct argument_reverser<false, T_reversed_arg_pack, T_type>
		{
			using reversed_arguments = decltype(Add_arg_to_front_of_pack<T_type>(T_reversed_arg_pack{}));
		};




		template<int I_target, int I_current, typename T_type, typename... T_args>
		struct get_argument_type_n {
			using arg_type = typename get_argument_type_n<I_target, I_current + 1, T_args...>::arg_type;
		};


		template<int I_shared, typename T_type, typename... T_args>
		struct get_argument_type_n<I_shared, I_shared, T_type, T_args...> {
			using arg_type = T_type;
		};


		template<int I_target, typename... T_deduced_args>
		constexpr auto Get_argument_type_from_pack_start(template_arg_pack<T_deduced_args...> pack)->get_argument_type_n<I_target, 0, T_deduced_args...>;

		


		template<typename T_arg_pack>
		struct inherit_from_args;

		template<typename... T_deduced_args>
		struct inherit_from_args<template_arg_pack<T_deduced_args...>> : T_deduced_args...{};




		template<int I_num, template<int, typename...> typename T_inherit, typename T_arg, typename... T_args>
		struct inherit_for_each;


		template<template<int, typename...> typename T_inherit, typename... T_deduced_args>
		constexpr auto Inherit_for_each_start(template_arg_pack<T_deduced_args...> arg_pack)->inherit_for_each<0, T_inherit, T_deduced_args...>;


		template<int I_num, template<int, typename...> typename T_inherit, typename T_arg, typename... T_tail>
		struct inherit_for_each : public inherit_for_each<I_num + 1, T_inherit, T_tail...> , public T_inherit<I_num, T_arg>  {};

		template<int I_num, template<int, typename...> typename T_inherit, typename T_arg>
		struct inherit_for_each<I_num, T_inherit, T_arg> : public T_inherit<I_num, T_arg> {};

	}
}




template<typename... T_types>
/* This type is a template_arg_pack type with a reversed version of T_types as arguments. */
using reverse_arguments = typename template_helpers::impl::argument_reverser<true, template_arg_pack<>, T_types...>::reversed_arguments;




template<typename T_arg_pack>
/* This type is a 'inherit_from_args' type, which inherits from all T_arg_pack's arguments, assuming T_arg_pack is a 'template_arg_pack'. */
using inherit_from_arg_pack_args = template_helpers::impl::inherit_from_args<T_arg_pack>;


template<template<int,typename...> typename T_inherit, typename T_args_pack>
/* Inherit T_inherit<argument number, argument> for all arguments in argument pack T_args_pack. */
using inherit_for_each_arg_in_pack = decltype(template_helpers::impl::Inherit_for_each_start<T_inherit>(T_args_pack{}));


template<template<int, typename...> typename T_inherit, typename... T_args>
/* Inherit T_inherit<argument number, argument> for all arguments in T_args. */
using inherit_for_each_arg = template_helpers::impl::inherit_for_each<0, T_inherit, T_args...>;




template<typename T_arg_pack, int I_arg_num>
/* Get the nth argument type from T_arg_pack. */
using get_argument_type_from_pack = typename decltype(template_helpers::impl::Get_argument_type_from_pack_start<I_arg_num>(T_arg_pack{}))::arg_type;




#endif // !TEMPLATE_HELPERS_H