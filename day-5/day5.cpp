#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

// seed-to-soil
// destination, source, range
// soil, seed

void fillInMap(std::vector<std::vector<std::tuple<long, long, long>>>& maps, int mapIndex, std::string line) {
    long destination, source, range;
    // std::cout << "Will Process: " << line << " into map " << mapIndex << std::endl;

    sscanf(line.c_str(), "%ld %ld %ld", &destination, &source, &range);
    std::tuple<long, long, long> mapEntry(destination, source, range);

    maps[mapIndex].push_back(mapEntry);
}

int main(int argc, char **argv) {
    std::string mapNames[7] = {"seed-to-soil map:", "soil-to-fertilizer map:", "fertilizer-to-water map:", "water-to-light map:", "light-to-temperature map:", "temperature-to-humidity map:", "humidity-to-location map:"};
    int numSeeds = 0;

    std::ifstream inputFile("sample.txt");

    std::string seedLine, junk;
    std::getline(inputFile, seedLine);
    std::getline(inputFile, junk);

    std::istringstream seedStream(seedLine);
    std::string seed;
    std::vector<long> seeds;

    while(seedStream >> seed) {
        if(seed != "seeds:") {
            seeds.push_back(std::stol(seed));
            numSeeds++;
        }
    }

    std::cout << "Seeds Read: ";
    for (int i = 0; i < seeds.size(); i++) {
        std::cout << seeds[i] << " ";
    }
    std::cout << std::endl;

    // 0 = source
    // 1 = destination
    // 2 = range
    // 0 seedToSoil;
    // 1 soilToFertilizer;
    // 2 fertilizerToWater;
    // 3 waterToLight;
    // 4 lightToTemperature;
    // 5 temperatureToHumidity;
    // 6 humidityToLocation;
    std::vector<std::vector<std::tuple<long, long, long>>> maps;
    maps.resize(7);

    std::string line;
    int mapIndex = 0;
    while (std::getline(inputFile, line)) {
        if(line == mapNames[mapIndex]) {
            continue;
        } else if(line == "") {
            mapIndex++;
            continue;
        } else {
            fillInMap(maps, mapIndex, line);
        }
    }

    for(int i = 0; i < maps.size(); i++) {
        printf("Map %d:\n", i);
        for(int j = 0; j < maps[i].size(); j++) {
            std::cout << std::get<0>(maps[i][j]) << " " << std::get<1>(maps[i][j]) << " " << std::get<2>(maps[i][j]);
            printf("\n");
        }
    }

    // destination, source, range
    long destination, source, range;
    for(int i = 0; i < numSeeds; i++) {
        for(int i = 0; i < maps.size(); i++) {
            for(int j = 0; j < maps[i].size(); j++) {
                destination = std::get<0>(maps[i][j]);
                source = std::get<1>(maps[i][j]); 
                range = std::get<2>(maps[i][j]);

                //something about mapping seeds/source into this range if it fits
                //if it does, don't need to look at other ranges and can continue to next map
                
            }
        }
    }

    inputFile.close();
}