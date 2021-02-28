function out_code = deg2code(in_deg)
    out_code = zeros(length(in_deg), 3);
    out_code(:, 1) = round(in_deg(:, 1) * 2^14/180, 0);
    out_code(:, 2) = round(in_deg(:, 2) * 2^14/180, 0);
    out_code(:, 3) = round(in_deg(:, 3), 0);
end
