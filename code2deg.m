function out_deg = code2deg(in_code)
    out_deg = zeros(length(in_code), 3);
    out_deg(:, 1) = in_code(:, 1) * 180/2^14;
    out_deg(:, 2) = in_code(:, 2) * 180/2^14;
    out_deg(:, 3) = in_code(:, 3);
end
