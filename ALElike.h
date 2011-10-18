// ALElike.h

#ifndef _ALE_LIKE_H_
#define _ALE_LIKE_H_

#include "ALEhelpers.h"
#include <math.h>

const static double lnfactconst2 = 0.918938533204672741780329;
const static double minLogLike = -60.0;
const static double SIGNIFICANT_LIBRARY_FRACTION = 0.02;

// casts a single numeric char to its int
int hackedIntCast(char c);

//uses Stirlings approximation to high precision
double lnfact2(double input);

// finds the insert probability (assuming normal distribution) P(point | N(0,sigma))
double GetInsertProbNormal(double point, const double sigma);

double getInsertLikelihoodBAM(bam1_t *read1, double mu, double var);

// finds the likelihood of a string of misses in read from seqPos to matchLen
double likeMiss(char *readQual, int seqPos, int missLen, int qOff);

// finds the likelihood of a string of matches in read from seqPos to matchLen
double likeMatch(char *readQual, int seqPos, int matchLen, int qOff);

// finds the likelihood of an insertion (right now it is the same as a miss)
double likeInsertion(char *readQual, int seqPos, int insertionLength, int qOff);

// finds the likelihood of an deletion (right now it is the same as a miss)
double likeDeletion(char *readQual, int seqPos, int deletionLength, int qOff);

// used to reduce likelihood in case of missmatches only
// (CIGAR already has accounted for matchlength, inserts, deletions)
double getMDLikelihood(char *MD, char *readQual, int qOff);

double getCIGARLikelihoodBAM(int numCigarOperations, uint32_t *cigar, char *readQual, int qOff, int *inserts, int *deletions, int *totalMatch);

// takes in a read and returns the match likelihood (due to matches, mismatches, indels)
double getMatchLikelihoodBAM(bam1_t *read, int qOff);

// returns the 2-bit hash representation of a nucl. given its place in the kmer
int kmerHash(char c1, int place);

// builds up a 2*kmerLen-bit hash (for the seq) given a seqenence and starting position
int getKmerHash(char *seq, int startPos, int kmerLen);

// calculates the kmer statistics
void computeKmerStats(assemblyT *theAssembly, int kmer);

// used in getPlacementWinner
unsigned int JSHash(char* str);

// finds the sum of the total likelihoods given the head of the list
double getTotalLikelihood(alignSet_t *head);

// find the placement winner
alignSet_t *getPlacementWinner(alignSet_t *head, double likeNormalizer, int *winner);

// apply statistics
void applyDepthAndMatchToContig(alignSet_t *alignment, contig_t *contig, double likeNormalizer);

// this applies the placement(s) to the assembly part (SINGLE PART)
// I feel like this could be sped up with a hash table vs the current linked lists, but we will see...
int applyPlacement(alignSet_t *head, assemblyT *theAssembly);

// compute the depth statistics
int computeDepthStats(assemblyT *theAssembly);

int guessQualityOffset(bam1_t *read);

libraryParametersT *computeLibraryParameters(samfile_t *ins, double outlierFraction, int qOff);

void tdestroy(void *root, void (*free_node)(void *nodep));
static int mateTreeCount = 0;

int mateTreeCmp(const void *pa, const void *pb);

alignSet_t *getOrStoreMateAlignment(void **mateTree, alignSet_t *thisAlignment, bam1_t *thisRead);


void mateTreeFreeNode(void *nodep);

void setSingleRead2Alignment(bam_header_t *header, alignSet_t *read2Only, alignSet_t *thisAlignment, bam1_t *thisReadMate, double likelihood);

enum MATE_ORIENTATION setAlignment(bam_header_t *header, assemblyT *theAssembly, alignSet_t *thisAlignment, alignSet_t *secondaryAlignment, void **mateTree, libraryParametersT *libParams, enum MATE_ORIENTATION orientation, bam1_t *thisRead, bam1_t *thisReadMate);

// divide by the expected likelihood of the read by the normalization factor Z (from Bayes rule)
// given only its length and the parameters of the distributions (See paper appendix)
double zNormalization(libraryMateParametersT *mateParams, bam1_t *thisRead, bam1_t *thisReadMate, int qOff);

void computeReadPlacements(samfile_t *ins, assemblyT *theAssembly, libraryParametersT *libParams, samfile_t *placementBam);

#endif
