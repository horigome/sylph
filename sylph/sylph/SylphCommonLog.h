﻿/**
 * @file     SylphCommonLog.h
 * @brief    Common LOG Functions
 * @author   M.Horigome
 * @version  1.0.0.0000
 * @date     2016-03-07 
 */
#pragma once
#include <Windows.h>

// * StdOut /
#define _OUTPUT _tprintf_s      

/**
 * @brief ログ関数
 * @param[in]  format_str ... printfスタイル
 */
inline void 
_TRACE_F_( _In_ LPCTSTR format_s, ... )
{
    TCHAR*      _msg_p =  NULL;
    va_list     _arg_list;

    va_start( _arg_list, format_s);

        const size_t _msg_len = _vsctprintf( format_s, _arg_list ) + 1;
        const size_t _size    =  _msg_len * sizeof( TCHAR ); 

        _msg_p  = ( TCHAR* )::malloc( _size );
        if ( !_msg_p ) goto  _TRACEF_END;

        ::ZeroMemory  ( _msg_p, _size );
        ::_vstprintf_s( _msg_p, _msg_len, format_s, _arg_list );

        _OUTPUT( _msg_p );

_TRACEF_END:
        if ( _msg_p ) ::free( _msg_p );

    va_end( _arg_list );
}

inline CAtlString 
_TRACE_HEAD( void ) {
    SYSTEMTIME _st;
    ::ZeroMemory( &_st, sizeof( _st ) );
    ::GetLocalTime( &_st );
    CAtlString _s;
    _s.Format( TEXT("[%04d-%02d-%02d %02d:%02d:%02d]: "),
        _st.wYear, _st.wMonth, _st.wDay, _st.wHour, _st.wMinute, _st.wSecond );
    return _s;
}

// *
// * Macro
// *

#ifdef UNICODE
    #define WIDEN2(x) L ## x
    #define WIDEN(x) WIDEN2(x)

    #define __FUNC__ WIDEN(__FUNCTION__)
    #define __UFILE__ WIDEN(__FILE__)
#else
    #define __UFUNC__ __FILE__
#endif

#define _STRACE( fmt, ...) _TRACE_F_( TEXT("[%s-(%04d)]: ") fmt, __UFILE__, __LINE__, __VA_ARGS__ )
#define _SLOG( fmt, ...) _TRACE_F_( TEXT("%s") fmt, _TRACE_HEAD(), __VA_ARGS__ )