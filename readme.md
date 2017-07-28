# HPDMBatchRun is developed to run batch calculations based on the Heat Pump Design Model (HPDM) program developed by ORNL.

# I/O format:
* input.txt, define one or two input parameters + start/interval; define output parameters
	* NPARA	3
	* INPUT	1:Vol_flow_rate_in:10:0.5:10	2:TI_C:75:1:5	2:MI_C:0.5:0.2:3
	* OUTPUT	6:TO_AIR	11:EER
* output.txt, summarize results
	* RUN	1:Vol_flow_rate_in	2:TI_C	2:MI_C	6:TO_AIR	11:EER
	* 1	10	75	0.5	0.5	5.6
	* 2	10.5	75	0.5	0.55	5.8
	* ...
	* 10	14.5	75	0.5	0.6	6.1
	* 11	10	76	0.5	0.7	6.1
	* ...
	* 50	14.5	79	0.5	0.7	7.2
	* 51	10	75	0.7	0.6	6.5
	* ...
	* 100	14.5	79	0.7	0.8	7.8
	* ...
	* 150	14.5	79	0.9 0.9	8.5
		
		
### last updated 7/28/17