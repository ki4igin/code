%u32 Az град = 180 * 2 ^-14 * az_in
%i32 At град = 180 * 2 ^-14 * el_in
%u32 r м     = r_in

function [az_out, el_out, r_out] = ParalaxCalc(az_in, el_in, r_in)
    %#codegen
    x_base = 29;
    y_base = 17;
    z_base = 11;

    %     x_base = 0;
    %     y_base = 0;
    %     z_base = 0;

    az_in_rad = az_in * pi / 2^14;
    el_in_rad = el_in * pi / 2^14;

    x_in = r_in .* cos(el_in_rad) .* cos(az_in_rad);
    y_in = r_in .* cos(el_in_rad) .* sin(az_in_rad);
    z_in = r_in .* sin(el_in_rad);

    x_out = x_in + x_base;
    y_out = y_in + y_base;
    z_out = z_in + z_base;

    r_out = sqrt(x_out.^2 + y_out.^2 + z_out.^2);
    el_out_rad = atan2(z_out, sqrt(x_out.^2 + y_out.^2));
    az_out_rad = atan2(y_out, x_out);

    if az_out_rad < 0
        az_out_rad = az_out_rad + 2 * pi;
    end

    az_out = az_out_rad * 2^14 / pi;
    el_out = el_out_rad * 2^14 / pi;

    az_out = uint32(az_out);
    el_out = int32(el_out);
    r_out = uint32(r_out);
end
