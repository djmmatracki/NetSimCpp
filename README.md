# Newtwork Simulation

Network simulation project implemented in C++.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name

NetSimCpp

## Description

The goal of the project is to design a system for modeling and simulating the operation of the network - on the example of production lines in a factory.

## Model

The production line in the factory (network) consists of the following elements (nodes), connected into a coherent whole.

- loading ramps (sources) - they deliver semi-finished products to the factory
- workers - they process semi-finished products
- storehouses (sinks) - they store semi-finished products after the end of the entire technological process.

The following combinations as part of the technological process are allowed:

- ramp -> worker
- worker -> worker
- worker -> storehouse

## Simulation

For a given network model (loaded from a file), we want to be able to simulate its operation - e.g. to check the potential efficiency of the production line.

The unit of time in the simulation is the turn. Each turn consists of stages that are resolved in the following order:

1. **Delivery** of the semi-finished products to the ramp.
2. **Handing over** semi-finished products to recipients.
3. **Processing** of semi-finished products by workers.
4. **Reporting** on simulation status.


## Reporting

The created system should enable two reporting options:

- network structure report
- report about the simulation status

Generated reports can be saved to a text file or to standard output.

## The scope of the application functionality

1. **Loading the network structure from the file.**
2. **Making possible modifications to the network structure and saving the new structure to a file.**
3. **Verification of the correctness of the loaded network.**
4. **Network operation simulation with reporting.**


## Authors
Dominik Matracki
Patryk Łyczko
