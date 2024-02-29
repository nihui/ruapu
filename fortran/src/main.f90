program main
    use ruapu, only: ruapu_init, ruapu_supports, ruapu_rua
    implicit none

    character(len=:), allocatable :: isa_supported(:)
    integer :: i

    print *, "ruapu initializing..."
    call ruapu_init()

    print *, "supports sse: ", ruapu_supports("sse")
    print *, "supports neon: ", ruapu_supports("neon")

    isa_supported = ruapu_rua()
    do i = 1, size(isa_supported)
        print *, trim(isa_supported(i))
    end do
end program main
