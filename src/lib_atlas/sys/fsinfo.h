/**
 * \file	system_info.h
 * \author	Thibaut Mattio <thibaut.mattio@gmail.com>
 * \date	18/07/2015
 * \copyright Copyright (c) 2015 Thibaut Mattio. All rights reserved.
 * Use of this source code is governed by the MIT license that can be
 * found in the LICENSE file.
 */

#ifndef ATLAS_SYSTEM_SYSTEM_INFO_H_
#define ATLAS_SYSTEM_SYSTEM_INFO_H_

#include <string>

#include <lib_atlas/macros.h>

namespace atlas {

namespace sys {

/**
 * Represent a unit of data.
 * A Unit can be a multiple of 10^3B, or a block.
 * The size of a block can be obtained by calling block_size();
 */
enum class BitUnit { BLOCK = 0, B, KB, MB, GB, TB };

/**
 * For a given directory and a bit unit, this method will return the
 * total space of the disk the given path is mounted on.
 *
 * \param unit Change it in order to get the output with a specific unit.
 * \param path A directory being contained by the mounted point to analyze.
 * \return The size of the mounted point where path is located in unit
 */
auto total_physical_memory(BitUnit unit = BitUnit::KB,
                           const char *path = ".") ATLAS_NOEXCEPT -> double;

/**
 * For a given directory and a bit unit, this method will return the
 * free space of the disk the given path is mounted on.
 *
 * The free space is the space available of the root user, not to be confunded
 * with the available space which is the space for other users.
 *
 * \param unit Change it in order to get the output with a specific unit.
 * \param path A directory being contained by the mounted point to analyze.
 * \return The free space on the mounted point where path is located in unit
 */
auto free_physical_memory(BitUnit unit = BitUnit::KB,
                          const char *path = ".") ATLAS_NOEXCEPT -> double;

/**
 * For a given directory and a bit unit, this method will return the
 * total space of the disk the given path is mounted on.
 *
 * The available space is the space available for all users, not to be confunded
 * with the free space which is the space for the root user.
 *
 * \param unit Change it in order to get the output with a specific unit.
 * \param path A directory being contained by the mounted point to analyze.
 * \return The available space on the mounted point where path is located in
 *unit
 */
auto available_physical_memory(BitUnit unit = BitUnit::KB,
                               const char *path = ".") ATLAS_NOEXCEPT -> double;

/**
 * For a given directory and a bit unit, this method will return the
 * used physical memory.
 *
 * It is using both the free space and the available space in order to
 * get an accurate used space.
 *
 * \param unit Change it in order to get the output with a specific unit.
 * \param path A directory being contained by the mounted point to analyze.
 * \return The size of the mounted point where path is located in unit
 */
auto used_physical_memory(BitUnit unit = BitUnit::KB,
                          const char *path = ".") ATLAS_NOEXCEPT -> double;

/**
 * Compare the total space of the mounted point with the used physical memory
 * to get a percentage of used physical memory.
 *
 * \param path A directory being contained by the mounted point to analyze.
 * \return The used space of the mounted point in percentage
 */
auto percentage_used_physical_memory(const char *path = ".")
    ATLAS_NOEXCEPT -> double;

/**
 * Compare the total space of the mounted point with the used physical memory
 * to get a percentage of available physical memory.
 *
 * \param path A directory being contained by the mounted point to analyze.
 * \return The available space of the mounted point in percentage
 */
static auto percentage_available_physical_memory(const char *path = ".")
    ATLAS_NOEXCEPT -> double;

/**
 * For the mounted point containing the given path, this will return the size
 * of the block used by the file system.
 *
 * This method is used internally for converting the different units.
 * When calling the statvfs structure, we are getting the size whith a block
 * size unit.
 *
 * \param path A directory being contained by the mounted point to analyze.
 * \return The size of the block for the file system used.
 */
auto block_size(const char *path = ".") ATLAS_NOEXCEPT -> uint64_t;

/**
 * For the mounted point containing the given path, this will return maximum
 * length of the filenames.
 *
 * \param path A directory being contained by the mounted point to analyze.
 * \return The maximum length of the filenames of the mounted point where path
 * is located in unit
 */
auto max_filename(const char *path = ".") ATLAS_NOEXCEPT -> uint64_t;

}  // namespace sys

}  // namespace atlas

#include <lib_atlas/sys/fsinfo_inl.h>

#endif  // ATLAS_SYSTEM_SYSTEM_INFO_H_
