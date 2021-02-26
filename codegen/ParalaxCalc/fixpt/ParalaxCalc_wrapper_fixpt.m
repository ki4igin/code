%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
%           Generated by MATLAB 9.9 and Fixed-Point Designer 7.1           %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [az_out,el_out,r_out] = ParalaxCalc_wrapper_fixpt(az_in,el_in,r_in)
    fm = get_fimath();
    az_in_in = fi( az_in, 0, 15, 0, fm );
    el_in_in = fi( el_in, 0, 13, 0, fm );
    r_in_in = fi( r_in, 0, 14, 0, fm );
    [az_out_out,el_out_out,r_out_out] = ParalaxCalc_fixpt( az_in_in, el_in_in, r_in_in );
    az_out = uint32( az_out_out );
    el_out = int32( el_out_out );
    r_out = uint32( r_out_out );
end

function fm = get_fimath()
	fm = fimath('RoundingMethod', 'Floor',...
	     'OverflowAction', 'Wrap',...
	     'ProductMode','FullPrecision',...
	     'SumMode','FullPrecision');
end