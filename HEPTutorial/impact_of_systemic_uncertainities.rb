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


x = 331.0 * ((331.0/473.85) * 0.1)
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
