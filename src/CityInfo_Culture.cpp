#include "CityInfo.h"
#include "Calc.h"
#include "Data/CityInfo.h"
#include "Data/Constants.h"

#define TOP(x) if (Data_CityInfo_CultureCoverage.x > 100) Data_CityInfo_CultureCoverage.x = 100;

void CityInfo_Culture_updateCoveragePercentages()
{
	// entertainment
	Data_CityInfo_CultureCoverage.theater = Calc_getPercentage(
		500 * Data_CityInfo_Buildings.theater.working, Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.amphitheater = Calc_getPercentage(
		800 * Data_CityInfo_Buildings.amphitheater.working, Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.colosseum = Calc_getPercentage(
		1500 * Data_CityInfo_Buildings.colosseum.working, Data_CityInfo.population);
	if (Data_CityInfo_Buildings.hippodrome.working <= 0) {
		Data_CityInfo_CultureCoverage.hippodrome = 0;
	} else {
		Data_CityInfo_CultureCoverage.hippodrome = 100;
	}
	TOP(theater);
	TOP(amphitheater);
	TOP(colosseum);

	// religion
	Data_CityInfo_CultureCoverage.religionCeres = Calc_getPercentage(
			500 * Data_CityInfo_Buildings.oracle.total +
			750 * Data_CityInfo_Buildings.smallTempleCeres.working +
			1500 * Data_CityInfo_Buildings.largeTempleCeres.working,
		Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.religionNeptune = Calc_getPercentage(
			500 * Data_CityInfo_Buildings.oracle.total +
			750 * Data_CityInfo_Buildings.smallTempleNeptune.working +
			1500 * Data_CityInfo_Buildings.largeTempleNeptune.working,
		Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.religionMercury = Calc_getPercentage(
			500 * Data_CityInfo_Buildings.oracle.total +
			750 * Data_CityInfo_Buildings.smallTempleMercury.working +
			1500 * Data_CityInfo_Buildings.largeTempleMercury.working,
		Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.religionMars = Calc_getPercentage(
			500 * Data_CityInfo_Buildings.oracle.total +
			750 * Data_CityInfo_Buildings.smallTempleMars.working +
			1500 * Data_CityInfo_Buildings.largeTempleMars.working,
		Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.religionVenus = Calc_getPercentage(
			500 * Data_CityInfo_Buildings.oracle.total +
			750 * Data_CityInfo_Buildings.smallTempleVenus.working +
			1500 * Data_CityInfo_Buildings.largeTempleVenus.working,
		Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.oracle = Calc_getPercentage(
		500 * Data_CityInfo_Buildings.oracle.total, Data_CityInfo.population);
	TOP(religionCeres);
	TOP(religionNeptune);
	TOP(religionMercury);
	TOP(religionMars);
	TOP(religionVenus);

	// education
	Data_CityInfo_CultureCoverage.school = Calc_getPercentage(
		75 * Data_CityInfo_Buildings.school.working, Data_CityInfo.populationSchoolAge);
	Data_CityInfo_CultureCoverage.library = Calc_getPercentage(
		800 * Data_CityInfo_Buildings.library.working, Data_CityInfo.population);
	Data_CityInfo_CultureCoverage.academy = Calc_getPercentage(
		100 * Data_CityInfo_Buildings.academy.working, Data_CityInfo.populationAcademyAge);
	TOP(school);
	TOP(library);
	TOP(academy);

	// health
	Data_CityInfo_CultureCoverage.hospital = Calc_getPercentage(
		1000 * Data_CityInfo_Buildings.hospital.working, Data_CityInfo.population);
	TOP(hospital);
}

void CityInfo_Culture_calculateDemandsForAdvisors()
{
	// emigration
	switch (Data_CityInfo.populationEmigrationCause) {
		case EmigrationCause_NoFood:
			Data_CityInfo.populationEmigrationCauseTextId = 2;
			break;
		case EmigrationCause_NoJobs:
			Data_CityInfo.populationEmigrationCauseTextId = 1;
			break;
		case EmigrationCause_HighTaxes:
			Data_CityInfo.populationEmigrationCauseTextId = 3;
			break;
		case EmigrationCause_LowWages:
			Data_CityInfo.populationEmigrationCauseTextId = 0;
			break;
		case EmigrationCause_ManyTents:
			Data_CityInfo.populationEmigrationCauseTextId = 4;
			break;
		default:
			Data_CityInfo.populationEmigrationCauseTextId = 5;
			break;
	}
	// health
	Data_CityInfo.healthDemand = 0;
	int max = 0;
	if (Data_CityInfo.housesRequiringBathhouseToEvolve > max) {
		Data_CityInfo.healthDemand = 1;
		max = Data_CityInfo.housesRequiringBathhouseToEvolve;
	}
	if (Data_CityInfo.housesRequiringBarberToEvolve > max) {
		Data_CityInfo.healthDemand = 2;
		max = Data_CityInfo.housesRequiringBarberToEvolve;
	}
	if (Data_CityInfo.housesRequiringClinicToEvolve > max) {
		Data_CityInfo.healthDemand = 3;
		max = Data_CityInfo.housesRequiringClinicToEvolve;
	}
	if (Data_CityInfo.housesRequiringHospitalToEvolve > max) {
		Data_CityInfo.healthDemand = 4;
	}
	// education
	Data_CityInfo.educationDemand = 0;
	if (Data_CityInfo.housesRequiringMoreEducationToEvolve > Data_CityInfo.housesRequiringEducationToEvolve) {
		Data_CityInfo.educationDemand = 1; // schools(academies?)
	} else if (Data_CityInfo.housesRequiringMoreEducationToEvolve == Data_CityInfo.housesRequiringEducationToEvolve) {
		Data_CityInfo.educationDemand = 2; // libraries
	} else if (Data_CityInfo.housesRequiringMoreEducationToEvolve || Data_CityInfo.housesRequiringEducationToEvolve) {
		Data_CityInfo.educationDemand = 3; // more education
	}
	// entertainment
	Data_CityInfo.entertainmentDemand = 0;
	if (Data_CityInfo.housesRequiringEntertainmentToEvolve > Data_CityInfo.housesRequiringMoreEntertainmentToEvolve) {
		Data_CityInfo.entertainmentDemand = 1;
	} else if (Data_CityInfo.housesRequiringMoreEntertainmentToEvolve) {
		Data_CityInfo.entertainmentDemand = 2;
	}
	// religion
	Data_CityInfo.religionDemand = 0;
	max = 0;
	if (Data_CityInfo.housesRequiringReligionToEvolve > max) {
		Data_CityInfo.religionDemand = 1;
		max = Data_CityInfo.housesRequiringReligionToEvolve;
	}
	if (Data_CityInfo.housesRequiringMoreReligionToEvolve > max) {
		Data_CityInfo.religionDemand = 2;
		max = Data_CityInfo.housesRequiringMoreReligionToEvolve;
	}
	if (Data_CityInfo.housesRequiringEvenMoreReligionToEvolve > max) {
		Data_CityInfo.religionDemand = 3;
	}
}