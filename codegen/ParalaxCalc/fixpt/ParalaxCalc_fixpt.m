%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
%           Generated by MATLAB 9.9 and Fixed-Point Designer 7.1           %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%u32 Az град = 180 * 2 ^-14 * az_in
%i32 At град = 180 * 2 ^-14 * el_in
%u32 r м     = r_in
function [az_out, el_out, r_out] = ParalaxCalc_fixpt(az_in, el_in, r_in)
    %#codegen
    fm = get_fimath();

    x_base = fi(29, 0, 32, 27, fm);
    y_base = fi(17, 0, 32, 27, fm);
    z_base = fi(11, 0, 32, 28, fm);

    %     x_base = 0;
    %     y_base = 0;
    %     z_base = 0;

    az_in_rad = fi(fi_div_by_shift(az_in * fi(pi, 0, 32, 30, fm), 14), 0, 32, 29, fm);
    el_in_rad = fi(fi_div_by_shift(el_in * fi(pi, 0, 32, 30, fm), 14), 1, 32, 30, fm);

    x_in = fi(r_in .* cos(el_in_rad) .* cos(az_in_rad), 1, 32, 14, fm);
    y_in = fi(r_in .* cos(el_in_rad) .* sin(az_in_rad), 1, 32, 14, fm);
    z_in = fi(r_in .* sin(el_in_rad), 1, 32, 14, fm);

    x_out = fi(x_in + x_base, 1, 32, 14, fm);
    y_out = fi(y_in + y_base, 1, 32, 14, fm);
    z_out = fi(z_in + z_base, 1, 32, 14, fm);

    r_out = fi(sqrt(x_out.^2 + y_out.^2 + z_out.^2), 0, 32, 14, fm);
    el_out_rad = fi(atan2(z_out, sqrt(x_out.^2 + y_out.^2)), 1, 32, 30, fm);
    az_out_rad = fi(atan2(y_out, x_out), 1, 32, 28, fm);

    if az_out_rad < fi(0, 0, 8, 0, fm)
        az_out_rad(:) = az_out_rad + fi(2 * pi, 0, 32, 29, fm);
    end

    az_out = fi(az_out_rad * fi(2^14, 0, 32, 17, fm)*fi(1/pi, 0, 32, 33, fm), 0, 32, 17, fm);
    el_out = fi(el_out_rad * fi(2^14, 0, 32, 17, fm)*fi(1/pi, 0, 32, 33, fm), 1, 32, 18, fm);

%     az_out = uint32(az_out);
%     el_out = int32(el_out);
%     r_out = uint32(r_out);
end



function y = fi_div_by_shift(a,shift_len)
    coder.inline( 'always' );
    if isfi( a )
        nt = numerictype( a );
        fm = fimath( a );
        nt_bs = numerictype( nt.Signed, nt.WordLength + shift_len, nt.FractionLength + shift_len );
        y = bitsra( fi( a, nt_bs, fm ), shift_len );
    else
        y = a / 2 ^ shift_len;
    end
end

function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Floor',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode', 'KeepMSB',...
	     'ProductWordLength', 64,...
	     'SumMode', 'KeepMSB',...
	     'SumWordLength', 64,...
	     'CastBeforeSum', true);
end
