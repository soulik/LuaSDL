if(WIN32)
	set(CMAKE_ASM_MASM_COMPILER nasm.exe)
	set(NASM_OBJ_FORMAT win32)
	set(NASM_DEBUG_FORMAT OBJ_FORMAT_win32)
elseif(UNIX)
	set(NASM_DEBUG_FORMAT OBJ_FORMAT_elf)
	if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
		set(CMAKE_ASM_MASM_COMPILER nasm)
		set(NASM_OBJ_FORMAT elf64)
	elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86")
		set(CMAKE_ASM_MASM_COMPILER nasm)
		set(NASM_OBJ_FORMAT elf32)
	endif()
endif()

function(nasm_command SRC_LIST_NAME OUT_LIST_NAME)
	set(ASM_OUT_LIST "")
	foreach(ASM_SRC ${${SRC_LIST_NAME}})
		get_filename_component(ASM_WE ${ASM_SRC} NAME_WE)
		get_filename_component(ASM_PATH ${ASM_SRC} DIRECTORY)
		set(ASM_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
		#set(ASM_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${ASM_PATH}")
		if (WIN32)
			set(ASM_OUT "${ASM_OUT_DIR}/${ASM_WE}.obj")
		else()
			set(ASM_OUT "${ASM_OUT_DIR}/${ASM_WE}.o")
		endif()
		list(APPEND ASM_OUT_LIST ${ASM_OUT})

		if (WIN32)
			set(NASM_ARGS -f ${NASM_OBJ_FORMAT} -d ${NASM_DEBUG_FORMAT})
		elseif(UNIX)
			set(NASM_ARGS -f ${NASM_OBJ_FORMAT} -d ${NASM_DEBUG_FORMAT})
		endif()

		add_custom_command(
			OUTPUT ${ASM_OUT}
			COMMAND ${CMAKE_ASM_MASM_COMPILER}
			ARGS ${NASM_ARGS} "${CMAKE_CURRENT_SOURCE_DIR}/${ASM_SRC}" -o "${ASM_OUT}" -I "${CMAKE_CURRENT_SOURCE_DIR}/${ASM_PATH}/"
			MAIN_DEPENDENCY ${ASM_SRC}
			COMMENT "generate ${ASM_OUT}"
		)
	endforeach()
	set (${OUT_LIST_NAME} ${ASM_OUT_LIST} PARENT_SCOPE)
endfunction()