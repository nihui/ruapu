!------------------------------------------------------------------------------
! Institution, Affiliation
!------------------------------------------------------------------------------
!
! MODULE:  ruapu
!
!> @author
!> mizu-bai
!
! DESCRIPTION: 
!> Fortran binding for ruapu
!> ruapu --- detect cpu isa features with single-file
!
! REVISION HISTORY:
! 29 Feb 2024 - Initial Version
!------------------------------------------------------------------------------
module ruapu
    implicit none

contains

subroutine ruapu_init()
    implicit none
    interface
        !> void ruapu_init()
        subroutine ruapu_init_() bind(c, name="ruapu_init")
            implicit none
        end subroutine ruapu_init_
        end interface
    call ruapu_init_()
end subroutine ruapu_init

integer function ruapu_supports(isa)
    use iso_c_binding, only: c_char, c_int, c_null_char
    implicit none

    character(len=*), intent(in) :: isa

    interface
        !> int ruapu_supports(const char* isa)
        integer(c_int) function ruapu_supports_(isa) bind(c, name="ruapu_supports")
            import c_int, c_char
            implicit none
            character(kind=c_char) :: isa
        end function ruapu_supports_
    end interface

    ruapu_supports = ruapu_supports_(trim(isa)//c_null_char)
end function ruapu_supports

function ruapu_rua()
    use iso_c_binding, only: c_char, c_f_pointer, c_ptr, c_null_char, c_int, c_null_ptr, C_NEW_LINE
    implicit none

    character(len=32), allocatable :: ruapu_rua(:)
    type(c_ptr), pointer :: isa_supported_ptrs(:) => null()
    character(len=1, kind=c_char), pointer :: isa_chars(:) => null()
    integer :: i, j, num_isa

    interface
        !> const char* const* ruapu_rua()
        type(c_ptr) function ruapu_rua_() bind(c, name="ruapu_rua")
            import c_ptr
            implicit none
        end function ruapu_rua_

        integer(c_int) function get_num_isa_supported() bind(c)
            import c_int
        end function
    end interface

    num_isa = get_num_isa_supported()
    call c_f_pointer(ruapu_rua_(), isa_supported_ptrs, (/num_isa/))
    allocate(ruapu_rua(num_isa))

    do i = 1, num_isa
        call c_f_pointer(isa_supported_ptrs(i), isa_chars, (/len(ruapu_rua(1))/))
        do j = 1, len(ruapu_rua(1))
            if (isa_chars(j) .eq. c_null_char) then
                exit
            end if
            ruapu_rua(i)(j: j) = isa_chars(j)
        end do
    end do
end function ruapu_rua

end module ruapu
