plot_prob = zeros(3,61);
plot_wind_speeds = [7 9 12];
plot_ws = 0:0.5:30;
for i = 1:length(plot_wind_speeds);
    scale = plot_wind_speeds(i)/gamma(1+(1/shape)); % (Manwell Ch 2)
    for j = 1:length(plot_ws);
    plot_prob(i,j) = wblpdf(plot_ws(j),scale,shape);
    end
end
figure
plot(0:0.5:30,plot_prob(1,:),0:0.5:30,plot_prob(2,:),0:0.5:30,plot_prob(3,:),...
    'LineWidth',2)
title('Wind Speed Distributions by Average Wind Speed')
xlabel('Wind Speed (m/s)')
ylabel('Probability')
legend('7 m/s','9 m/s','12 m/s')


labels = {'Turbine','Development & Consent','Insurance','Decommissioning',...
    'Other','Foundation','Installation','Interarray Electrical','Grid Connection'};
figure
pie(subplot(1,2,1),[turbine_low,d_and_c_low,insurance_low,decommissioning_low,other,...
    substructure_low(2),install_m(2),...
    (electrical_by_depth(2)+electrical_install_by_depth(2)),...
    (hvac_by_distance(2)+hvac_install_by_distance(2)+base_hvac)],labels);

pie(subplot(1,2,2),[turbine_high,d_and_c_high,insurance_high,decommissioning_high,other,...
    substructure_high(2),install_m(2),...
    (electrical_by_depth(2)+electrical_install_by_depth(2)),...
    (hvac_by_distance(2)+hvac_install_by_distance(2)+base_hvac)],labels);

figure
plot(subplot(2,1,1),distance,total_capital_low(:,2),distance,total_capital_high(:,2),...
    'LineWidth',2)
title('Cost vs. Distance')
xlabel('Distance (nm)')
ylabel('Capital Cost ($/kW)')
legend('Low','High')
plot(subplot(2,1,2),depth,total_capital_low(2,:),depth,total_capital_high(2,:),...
    'LineWidth',2)
title('Cost vs. Depth')
xlabel('Depth (m)')
ylabel('Capital Cost ($/kW)')

figure
p_CA = plot(CA_1_high_l_cum,1000*to_gcam_dollars*CA_1_high_l_sort(:,2),...
    CA_1_low_h_cum,1000*to_gcam_dollars*CA_1_low_h_sort(:,2),...
    CA_2_high_l_cum,1000*to_gcam_dollars*CA_2_high_l_sort(:,2),...
    CA_2_low_h_cum,1000*to_gcam_dollars*CA_2_low_h_sort(:,2),...
    CA_3_high_l_cum,1000*to_gcam_dollars*CA_3_high_l_sort(:,2),...
    CA_3_low_h_cum,1000*to_gcam_dollars*CA_3_low_h_sort(:,2),...
    CA_4_high_l_cum,1000*to_gcam_dollars*CA_4_high_l_sort(:,2),...
    CA_4_low_h_cum,1000*to_gcam_dollars*CA_4_low_h_sort(:,2),...
    CA_5_high_l_cum,1000*to_gcam_dollars*CA_5_high_l_sort(:,2),...
    CA_5_low_h_cum,1000*to_gcam_dollars*CA_5_low_h_sort(:,2),...
    CA_6_high_l_cum,1000*to_gcam_dollars*CA_6_high_l_sort(:,2),...
    CA_6_low_h_cum,1000*to_gcam_dollars*CA_6_low_h_sort(:,2),...
    CA_7_high_l_cum,1000*to_gcam_dollars*CA_7_high_l_sort(:,2),...
    CA_7_low_h_cum,1000*to_gcam_dollars*CA_7_low_h_sort(:,2),...
    'LineWidth',2);
title('California','FontSize', 16);
xlabel('Annual Energy (EJ/yr)','FontSize', 16);
ylabel('LCOE ($/MWh)','FontSize', 16);
set(p_CA,{'Color'},...
    {[1 0 0],[1 0 0],[1 0 1],[1 0 1],...
    [1 1 0],[1 1 0],[0 1 0],[0 1 0],...
    [0 1 1],[0 1 1],[0 0 1],[0 0 1],...
    [0 0 0],[0 0 0]}');
set(p_CA,{'LineStyle'},...
    {'-','--','-','--','-','--',...
    '-','--','-','--','-','--',...
    '-','--'}');
l_CA = legend('7.0-7.5 m/s low cost','7.0-7.5 m/s high cost',...
    '7.5-8.0 m/s low cost','7.5-8.0 m/s high cost',...
    '8.0-8.5 m/s low cost','8.0-8.5 m/s high cost',...
    '8.5-9.0 m/s low cost','8.5-9.0 m/s high cost',...
    '9.0-9.5 m/s low cost','9.0-9.5 m/s high cost',...
    '9.5-10.0 m/s low cost','9.5-10.0 m/s high cost',...
    '10.0-10.5 m/s low cost','10.0-10.5 m/s high cost',...
    'Location','eastoutside');
set(l_CA,'FontSize',12);

figure
p_MA = plot(MA_1_high_l_cum,1000*to_gcam_dollars*MA_1_high_l_sort(:,2),...
    MA_1_low_h_cum,1000*to_gcam_dollars*MA_1_low_h_sort(:,2),...
    MA_2_high_l_cum,1000*to_gcam_dollars*MA_2_high_l_sort(:,2),...
    MA_2_low_h_cum,1000*to_gcam_dollars*MA_2_low_h_sort(:,2),...
    MA_3_high_l_cum,1000*to_gcam_dollars*MA_3_high_l_sort(:,2),...
    MA_3_low_h_cum,1000*to_gcam_dollars*MA_3_low_h_sort(:,2),...
    MA_4_high_l_cum,1000*to_gcam_dollars*MA_4_high_l_sort(:,2),...
    MA_4_low_h_cum,1000*to_gcam_dollars*MA_4_low_h_sort(:,2),...
    MA_5_high_l_cum,1000*to_gcam_dollars*MA_5_high_l_sort(:,2),...
    MA_5_low_h_cum,1000*to_gcam_dollars*MA_5_low_h_sort(:,2),...
    MA_6_high_l_cum,1000*to_gcam_dollars*MA_6_high_l_sort(:,2),...
    MA_6_low_h_cum,1000*to_gcam_dollars*MA_6_low_h_sort(:,2),...
    MA_7_high_l_cum,1000*to_gcam_dollars*MA_7_high_l_sort(:,2),...
    MA_7_low_h_cum,1000*to_gcam_dollars*MA_7_low_h_sort(:,2),...
    'LineWidth',2);
title('Massachusetts','FontSize', 16);
xlabel('Annual Energy (EJ/yr)','FontSize', 16);
ylabel('LCOE ($/MWh)','FontSize', 16);
set(p_MA,{'Color'},...
    {[1 0 0],[1 0 0],[1 0 1],[1 0 1],...
    [1 1 0],[1 1 0],[0 1 0],[0 1 0],...
    [0 1 1],[0 1 1],[0 0 1],[0 0 1],...
    [0 0 0],[0 0 0]}');
set(p_MA,{'LineStyle'},...
    {'-','--','-','--','-','--',...
    '-','--','-','--','-','--',...
    '-','--',}');
l_MA = legend('7.0-7.5 m/s low cost','7.0-7.5 m/s high cost',...
    '7.5-8.0 m/s low cost','7.5-8.0 m/s high cost',...
    '8.0-8.5 m/s low cost','8.0-8.5 m/s high cost',...
    '8.5-9.0 m/s low cost','8.5-9.0 m/s high cost',...
    '9.0-9.5 m/s low cost','9.0-9.5 m/s high cost',...
    '9.5-10.0 m/s low cost','9.5-10.0 m/s high cost',...
    '10.0-10.5 m/s low cost','10.0-10.5 m/s high cost',...
    'Location','eastoutside');
set(l_MA,'FontSize',12);

figure
p_MD = plot(MD_1_low_l_cum,MD_1_low_l_sort(:,2),MD_1_high_l_cum,MD_1_high_l_sort(:,2),...
    MD_1_low_h_cum,MD_1_low_h_sort(:,2),MD_1_high_h_cum,MD_1_high_h_sort(:,2),...
    MD_2_low_l_cum,MD_2_low_l_sort(:,2),MD_2_high_l_cum,MD_2_high_l_sort(:,2),...
    MD_2_low_h_cum,MD_2_low_h_sort(:,2),MD_2_high_h_cum,MD_2_high_h_sort(:,2),...
    MD_3_low_l_cum,MD_3_low_l_sort(:,2),MD_3_high_l_cum,MD_3_high_l_sort(:,2),...
    MD_3_low_h_cum,MD_3_low_h_sort(:,2),MD_3_high_h_cum,MD_3_high_h_sort(:,2),...
    MD_4_low_l_cum,MD_4_low_l_sort(:,2),MD_4_high_l_cum,MD_4_high_l_sort(:,2),...
    MD_4_low_h_cum,MD_4_low_h_sort(:,2),MD_4_high_h_cum,MD_4_high_h_sort(:,2),...
    MD_5_low_l_cum,MD_5_low_l_sort(:,2),MD_5_high_l_cum,MD_5_high_l_sort(:,2),...
    MD_5_low_h_cum,MD_5_low_h_sort(:,2),MD_5_high_h_cum,MD_5_high_h_sort(:,2),...
    MD_6_low_l_cum,MD_6_low_l_sort(:,2),MD_6_high_l_cum,MD_6_high_l_sort(:,2),...
    MD_6_low_h_cum,MD_6_low_h_sort(:,2),MD_6_high_h_cum,MD_6_high_h_sort(:,2),...
    MD_7_low_l_cum,MD_7_low_l_sort(:,2),MD_7_high_l_cum,MD_7_high_l_sort(:,2),...
    MD_7_low_h_cum,MD_7_low_h_sort(:,2),MD_7_high_h_cum,MD_7_high_h_sort(:,2),...
    'LineWidth',2);
title('Maryland','FontSize', 16);
xlabel('Annual Energy (EJ/yr)','FontSize', 16);
ylabel('LCOE (1975$/kWh)','FontSize', 16);
set(p_MD,{'Color'},...
    {[1 0 0],[1 0 0],[1 0 0],[1 0 0],[1 0 1],[1 0 1],[1 0 1],[1 0 1],...
    [1 1 0],[1 1 0],[1 1 0],[1 1 0],[0 1 0],[0 1 0],[0 1 0],[0 1 0],...
    [0 1 1],[0 1 1],[0 1 1],[0 1 1],[0 0 1],[0 0 1],[0 0 1],[0 0 1],...
    [0 0 0],[0 0 0],[0 0 0],[0 0 0]}');
set(p_MD,{'LineStyle'},...
    {'-','--',':','-.','-','--',':','-.','-','--',':','-.',...
    '-','--',':','-.','-','--',':','-.','-','--',':','-.',...
    '-','--',':','-.'}');
l_MD = legend('7.0-7.5 m/s low, low','7.0-7.5 m/s high, low','7.0-7.5 m/s low, high','7.0-7.5 m/s high, high',...
    '7.5-8.0 m/s low, low','7.5-8.0 m/s high, low','7.5-8.0 m/s low, high','7.5-8.0 m/s high, high',...
    '8.0-8.5 m/s low, low','8.0-8.5 m/s high, low','8.0-8.5 m/s low, high','8.0-8.5 m/s high, high',...
    '8.5-9.0 m/s low, low','8.5-9.0 m/s high, low','8.5-9.0 m/s low, high','8.5-9.0 m/s high, high',...
    '9.0-9.5 m/s low, low','9.0-9.5 m/s high, low','9.0-9.5 m/s low, high','9.0-9.5 m/s high, high',...
    '9.5-10.0 m/s low, low','9.5-10.0 m/s high, low','9.5-10.0 m/s low, high','9.5-10.0 m/s high, high',...
    '10.0-10.5 m/s low, low','10.0-10.5 m/s high, low','10.0-10.5 m/s low, high','10.0-10.5 m/s high, high',...
    'Location','eastoutside');
set(l_MD,'FontSize',12);

% low cost, high energy
CA_total_high = [CA_1_high_l(:,1),1000*to_gcam_dollars*CA_1_high_l(:,2);    
    CA_2_high_l(:,1),1000*to_gcam_dollars*CA_2_high_l(:,2);
    CA_3_high_l(:,1),1000*to_gcam_dollars*CA_3_high_l(:,2);
    CA_4_high_l(:,1),1000*to_gcam_dollars*CA_4_high_l(:,2);
    CA_5_high_l(:,1),1000*to_gcam_dollars*CA_5_high_l(:,2);
    CA_6_high_l(:,1),1000*to_gcam_dollars*CA_6_high_l(:,2);
    CA_7_high_l(:,1),1000*to_gcam_dollars*CA_7_high_l(:,2)];
CA_total_high = sortrows(CA_total_high,2)

MA_total_high = [MA_1_high_l(:,1),1000*to_gcam_dollars*MA_1_high_l(:,2);    
    MA_2_high_l(:,1),1000*to_gcam_dollars*MA_2_high_l(:,2);
    MA_3_high_l(:,1),1000*to_gcam_dollars*MA_3_high_l(:,2);
    MA_4_high_l(:,1),1000*to_gcam_dollars*MA_4_high_l(:,2);
    MA_5_high_l(:,1),1000*to_gcam_dollars*MA_5_high_l(:,2);
    MA_6_high_l(:,1),1000*to_gcam_dollars*MA_6_high_l(:,2);
    MA_7_high_l(:,1),1000*to_gcam_dollars*MA_7_high_l(:,2)];
MA_total_high = sortrows(MA_total_high,2)

MD_total_high = [MD_1_high_l(:,1),1000*to_gcam_dollars*MD_1_high_l(:,2);    
    MD_2_high_l(:,1),1000*to_gcam_dollars*MD_2_high_l(:,2);
    MD_3_high_l(:,1),1000*to_gcam_dollars*MD_3_high_l(:,2);
    MD_4_high_l(:,1),1000*to_gcam_dollars*MD_4_high_l(:,2);
    MD_5_high_l(:,1),1000*to_gcam_dollars*MD_5_high_l(:,2);
    MD_6_high_l(:,1),1000*to_gcam_dollars*MD_6_high_l(:,2);
    MD_7_high_l(:,1),1000*to_gcam_dollars*MD_7_high_l(:,2)];
MD_total_high = sortrows(MD_total_high,2)

MI_total_high = [MI_1_high_l(:,1),1000*to_gcam_dollars*MI_1_high_l(:,2);    
    MI_2_high_l(:,1),1000*to_gcam_dollars*MI_2_high_l(:,2);
    MI_3_high_l(:,1),1000*to_gcam_dollars*MI_3_high_l(:,2);
    MI_4_high_l(:,1),1000*to_gcam_dollars*MI_4_high_l(:,2);
    MI_5_high_l(:,1),1000*to_gcam_dollars*MI_5_high_l(:,2);
    MI_6_high_l(:,1),1000*to_gcam_dollars*MI_6_high_l(:,2);
    MI_7_high_l(:,1),1000*to_gcam_dollars*MI_7_high_l(:,2)];
MI_total_high = sortrows(MI_total_high,2)

% high cost, low energy
CA_total_low = [CA_1_low_h(:,1),1000*to_gcam_dollars*CA_1_low_h(:,2);    
    CA_2_low_l(:,1),1000*to_gcam_dollars*CA_2_low_l(:,2);
    CA_3_low_l(:,1),1000*to_gcam_dollars*CA_3_low_l(:,2);
    CA_4_low_l(:,1),1000*to_gcam_dollars*CA_4_low_l(:,2);
    CA_5_low_l(:,1),1000*to_gcam_dollars*CA_5_low_l(:,2);
    CA_6_low_l(:,1),1000*to_gcam_dollars*CA_6_low_l(:,2);
    CA_7_low_l(:,1),1000*to_gcam_dollars*CA_7_low_l(:,2)];
CA_total_low = sortrows(CA_total_low,2)

MA_total_low = [MA_1_low_h(:,1),1000*to_gcam_dollars*MA_1_low_h(:,2);    
    MA_2_low_l(:,1),1000*to_gcam_dollars*MA_2_low_l(:,2);
    MA_3_low_l(:,1),1000*to_gcam_dollars*MA_3_low_l(:,2);
    MA_4_low_l(:,1),1000*to_gcam_dollars*MA_4_low_l(:,2);
    MA_5_low_l(:,1),1000*to_gcam_dollars*MA_5_low_l(:,2);
    MA_6_low_l(:,1),1000*to_gcam_dollars*MA_6_low_l(:,2);
    MA_7_low_l(:,1),1000*to_gcam_dollars*MA_7_low_l(:,2)];
MA_total_low = sortrows(MA_total_low,2)

MD_total_low = [MD_1_low_h(:,1),1000*to_gcam_dollars*MD_1_low_h(:,2);    
    MD_2_low_l(:,1),1000*to_gcam_dollars*MD_2_low_l(:,2);
    MD_3_low_l(:,1),1000*to_gcam_dollars*MD_3_low_l(:,2);
    MD_4_low_l(:,1),1000*to_gcam_dollars*MD_4_low_l(:,2);
    MD_5_low_l(:,1),1000*to_gcam_dollars*MD_5_low_l(:,2);
    MD_6_low_l(:,1),1000*to_gcam_dollars*MD_6_low_l(:,2);
    MD_7_low_l(:,1),1000*to_gcam_dollars*MD_7_low_l(:,2)];
MD_total_low = sortrows(MD_total_low,2)

MI_total_low = [MI_1_low_h(:,1),1000*to_gcam_dollars*MI_1_low_h(:,2);    
    MI_2_low_l(:,1),1000*to_gcam_dollars*MI_2_low_l(:,2);
    MI_3_low_l(:,1),1000*to_gcam_dollars*MI_3_low_l(:,2);
    MI_4_low_l(:,1),1000*to_gcam_dollars*MI_4_low_l(:,2);
    MI_5_low_l(:,1),1000*to_gcam_dollars*MI_5_low_l(:,2);
    MI_6_low_l(:,1),1000*to_gcam_dollars*MI_6_low_l(:,2);
    MI_7_low_l(:,1),1000*to_gcam_dollars*MI_7_low_l(:,2)];
MI_total_low = sortrows(MI_total_low,2)

CA_total_high_cum = [zeros(size(CA_total_high,1),1) CA_total_high(:,2)];
CA_total_low_cum = [zeros(size(CA_total_low,1),1) CA_total_low(:,2)];
MA_total_high_cum = [zeros(size(MA_total_high,1),1) MA_total_high(:,2)];
MA_total_low_cum = [zeros(size(MA_total_low,1),1) MA_total_low(:,2)];
MD_total_high_cum = [zeros(size(MD_total_high,1),1) MD_total_high(:,2)];
MD_total_low_cum = [zeros(size(MD_total_low,1),1) MD_total_low(:,2)];
MI_total_high_cum = [zeros(size(MI_total_high,1),1) MI_total_high(:,2)];
MI_total_low_cum = [zeros(size(MI_total_low,1),1) MI_total_low(:,2)];
for i = 1:size(MA_total_high,1);
    CA_total_high_cum(i,1) = sum(CA_total_high(1:i,1));
    CA_total_low_cum(i,1) = sum(CA_total_low(1:i,1));
    MA_total_high_cum(i,1) = sum(MA_total_high(1:i,1));
    MA_total_low_cum(i,1) = sum(MA_total_low(1:i,1));
    MD_total_high_cum(i,1) = sum(MD_total_high(1:i,1));
    MD_total_low_cum(i,1) = sum(MD_total_low(1:i,1));
    MI_total_high_cum(i,1) = sum(MI_total_high(1:i,1));
    MI_total_low_cum(i,1) = sum(MI_total_low(1:i,1));
end
figure
p_MA_total = plot(MA_total_high_cum(:,1),MA_total_high_cum(:,2),...
    MA_total_low_cum(:,1),MA_total_low_cum(:,2),...
    CA_total_high_cum(:,1),CA_total_high_cum(:,2),...
    CA_total_low_cum(:,1),CA_total_low_cum(:,2),...
    MD_total_high_cum(:,1),MD_total_high_cum(:,2),...
    MD_total_low_cum(:,1),MD_total_low_cum(:,2),...
    'LineWidth',2)
xlabel('Annual Generation (EJ/year)')
ylabel('LCOE ($/MWh)')
title('State Offshore Wind Energy Supply Curves')
legend('MA Low Cost','MA High Cost','CA Low Cost','CA High Cost','MD Low Cost','MD High Cost')
set(p_MA_total,{'LineStyle'},{'-','--','-','--','-','--'}');
set(p_MA_total,{'Color'},{'r','r','b','b','g','g'}');


years = 2015:5:2100;
figure
cap_time = plot(years',cap1l_over_time(5:end,1),years,cap1h_over_time(5:end,1),...
    years',cap1l_adv_over_time(5:end,1),years,cap1h_adv_over_time(5:end,1),...
    'LineWidth',2)
title('Cost vs. Time')
xlabel('Year')
ylabel('Capital Cost ($/kW)')
legend('Low Cost','High Cost','Low Cost, Rapid Tech Change','High Cost, Rapid Tech Change')
set(cap_time,{'LineStyle'},{'-','-','--','--'}');
set(cap_time,{'Color'},{'b','r','b','r'}');

