# OUTPUT OF THIS SCRIPT
# mc_tt_bar_events: 7929.18
# mc_tt_bar_events_hlt: 1001.8
# mc_trigger_effiency: 0.1263434554392762
# mc_tt_bar_events_after_cuts: 350.0
# mc_acceptance: 0.34937113196246755
# data_tt_bar_events_after_cuts_and_background_substraction: 331.0
# data_tt_bar_total_events: 7498.7388
# data_luminosity: 50.0
# data_tt_bar_cross_section: 149.974776

# 149.974776 | 136.34070545454546 - 166.63864 | 0.9090909090909092 1.1111111111111112
# change: 0.09090909090909083
# 149.974776 | 142.83312 - 157.8681852631579 | 0.9523809523809524 1.0526315789473686
# change: 0.04761904761904756
# 149.974776 | 134.9772984 - 164.97225360000004 | 0.9 1.1000000000000003
# change: 0.09999999999999998
# 149.974776 | 139.4985386134853 - 160.4510133865147 | 0.9301466708874118 1.0698533291125882
# change: 0.06985332911258824
# sqrt(a*a + b*b + c*c + d*d) = 0.15940992470412255
# 126.06730825032236 - 173.88224374967763



mc_tt_bar_events = 7929.18
mc_tt_bar_events_hlt = 1001.8
mc_trigger_effiency = mc_tt_bar_events_hlt / mc_tt_bar_events
mc_tt_bar_events_after_cuts = 350.0
mc_acceptance = mc_tt_bar_events_after_cuts / mc_tt_bar_events_hlt

data_tt_bar_events_after_cuts_and_background_substraction = 331.0
data_tt_bar_total_events = (331.0 / mc_trigger_effiency) / mc_acceptance
data_luminosity = 50.0
data_tt_bar_cross_section = data_tt_bar_total_events / data_luminosity

puts "mc_tt_bar_events: #{mc_tt_bar_events}"
puts "mc_tt_bar_events_hlt: #{mc_tt_bar_events_hlt}"
puts "mc_trigger_effiency: #{mc_trigger_effiency}"
puts "mc_tt_bar_events_after_cuts: #{mc_tt_bar_events_after_cuts}"
puts "mc_acceptance: #{mc_acceptance}"
puts "data_tt_bar_events_after_cuts_and_background_substraction: #{data_tt_bar_events_after_cuts_and_background_substraction}"
puts "data_tt_bar_total_events: #{data_tt_bar_total_events}"
puts "data_luminosity: #{data_luminosity}"
puts "data_tt_bar_cross_section: #{data_tt_bar_cross_section}\n\n"

luminosity_uncertainty = 0.1
btagging_efficiency_uncertainity = 0.1
trigger_efficiency_uncertainity = 0.05
crosssection_uncertainity_on_background_events = 0.1

changes = []

data_luminosity_min = data_luminosity - (data_luminosity*luminosity_uncertainty)
data_luminosity_max = data_luminosity + (data_luminosity*luminosity_uncertainty)
data_tt_bar_cross_section_max = data_tt_bar_total_events / data_luminosity_min
data_tt_bar_cross_section_min = data_tt_bar_total_events / data_luminosity_max
puts "#{data_tt_bar_cross_section} | #{data_tt_bar_cross_section_min} - #{data_tt_bar_cross_section_max} | #{data_tt_bar_cross_section_min/data_tt_bar_cross_section} #{data_tt_bar_cross_section_max/data_tt_bar_cross_section}"
change = 1 - (data_tt_bar_cross_section_min/data_tt_bar_cross_section)
changes << change
puts "change: #{change}"

mc_trigger_effiency_min = mc_trigger_effiency - (mc_trigger_effiency*trigger_efficiency_uncertainity)
mc_trigger_effiency_max = mc_trigger_effiency + (mc_trigger_effiency*trigger_efficiency_uncertainity)
data_tt_bar_cross_section_max = ((331.0 / mc_trigger_effiency_min) / mc_acceptance) / data_luminosity
data_tt_bar_cross_section_min = ((331.0 / mc_trigger_effiency_max) / mc_acceptance) / data_luminosity
puts "#{data_tt_bar_cross_section} | #{data_tt_bar_cross_section_min} - #{data_tt_bar_cross_section_max} | #{data_tt_bar_cross_section_min/data_tt_bar_cross_section} #{data_tt_bar_cross_section_max/data_tt_bar_cross_section}"
change = 1 - (data_tt_bar_cross_section_min/data_tt_bar_cross_section)
changes << change
puts "change: #{change}"

data_tt_bar_events = 331.0
data_tt_bar_events_min = data_tt_bar_events - (data_tt_bar_events*crosssection_uncertainity_on_background_events)
data_tt_bar_events_max = data_tt_bar_events + (data_tt_bar_events*crosssection_uncertainity_on_background_events)
data_tt_bar_cross_section_min = ((data_tt_bar_events_min / mc_trigger_effiency) / mc_acceptance) / data_luminosity
data_tt_bar_cross_section_max = ((data_tt_bar_events_max / mc_trigger_effiency) / mc_acceptance) / data_luminosity
puts "#{data_tt_bar_cross_section} | #{data_tt_bar_cross_section_min} - #{data_tt_bar_cross_section_max} | #{data_tt_bar_cross_section_min/data_tt_bar_cross_section} #{data_tt_bar_cross_section_max/data_tt_bar_cross_section}"
change = 1 - (data_tt_bar_cross_section_min/data_tt_bar_cross_section)
changes << change
puts "change: #{change}"


x = 331.0 * ((331.0/473.85) * btagging_efficiency_uncertainity)
data_tt_bar_cross_section_min = (( (331.0 - x ) / mc_trigger_effiency) / mc_acceptance) / data_luminosity
data_tt_bar_cross_section_max = (( (331.0 + x ) / mc_trigger_effiency) / mc_acceptance) / data_luminosity
puts "#{data_tt_bar_cross_section} | #{data_tt_bar_cross_section_min} - #{data_tt_bar_cross_section_max} | #{data_tt_bar_cross_section_min/data_tt_bar_cross_section} #{data_tt_bar_cross_section_max/data_tt_bar_cross_section}"
change = 1 - (data_tt_bar_cross_section_min/data_tt_bar_cross_section)
changes << change
puts "change: #{change}"

changes = Math.sqrt(changes.map do |change|
  change ** 2
end.inject(0, &:+))

puts "sqrt(a*a + b*b + c*c + d*d) = #{changes}"


data_tt_bar_cross_section_min = data_tt_bar_cross_section - (data_tt_bar_cross_section*changes)
data_tt_bar_cross_section_max = data_tt_bar_cross_section + (data_tt_bar_cross_section*changes)

puts "#{data_tt_bar_cross_section_min} - #{data_tt_bar_cross_section_max}"
