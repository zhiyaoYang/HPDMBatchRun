# HPDMBatchRun is developed to run batch calculations based on the Heat Pump Design Model (HPDM) program developed by ORNL.

# I/O format:
* input.txt, define one or two input parameters + start/interval; define output parameters
	* NPARA	2
	* INPUT	1:Vol_flow_rate_in:10:0.5:10	2:TI_C:75:1:5
	* OUTPUT	6:TO_AIR	11:EER
* output.txt, summarize results
	* RUN	1:Vol_flow_rate_in	2:TI_C	6:TO_AIR	11:EER
	* 1	10	75	0.5	5.6
	* 2	10.5	75	0.55	5.8
	* ...
	* 11	10	76	0.7	6.1
	* ...
	* 50	15	80	0.7	7.2
		
		
### last updated 7/27/17