/*
 * BSD 2-Clause License
 *
 * Copyright (c) 2021, Christoph Neuhauser
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SGL_DEVICE_HPP
#define SGL_DEVICE_HPP

#include <string>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <optional>
#include <functional>
#include <memory>
#include <thread>

#include <vulkan/vulkan.h>
#include "VulkanCompat.hpp"

struct DeviceFeatures {
    DeviceFeatures() {
        timelineSemaphoreFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES;
        bufferDeviceAddressFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
        scalarBlockLayoutFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES;
        uniformBufferStandardLayoutFeaturesKhr.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES;
        shaderFloat16Int8Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES;
        device16BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES;
        device8BitStorageFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES;
        shaderDrawParametersFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES;
        subgroupSizeControlFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES;
        accelerationStructureFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
        rayTracingPipelineFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
        rayQueryFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR;
        fragmentShaderInterlockFeatures.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT;
        shaderAtomicInt64Features.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES_KHR;
        shaderImageAtomicInt64Features.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT;
        shaderAtomicFloatFeatures.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT;
#ifdef VK_EXT_mutable_descriptor_type
        mutableDescriptorTypeFeatures.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT;
#endif
#ifdef VK_EXT_shader_atomic_float2
        shaderAtomicFloat2Features.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT;
#endif
#ifdef VK_KHR_shader_bfloat16
        shaderBfloat16Features.sType =
                VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_BFLOAT16_FEATURES_KHR;
#endif
        meshShaderFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV;
#ifdef VK_EXT_mesh_shader
        meshShaderFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT;
#endif
#ifdef VK_NV_cooperative_matrix
        cooperativeMatrixFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV;
#endif
#ifdef VK_KHR_cooperative_matrix
        cooperativeMatrixFeaturesKHR.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR;
#endif
#ifdef VK_NV_cooperative_matrix2
        cooperativeMatrix2FeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_2_FEATURES_NV;
#endif
#ifdef VK_NV_cooperative_vector
        cooperativeVectorFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_VECTOR_FEATURES_NV;
#endif
#ifdef VK_EXT_shader_64bit_indexing
        shader64BitIndexingFeaturesEXT.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_64_BIT_INDEXING_FEATURES_EXT;
#endif
#ifdef VK_NV_ray_tracing_linear_swept_spheres
        rayTracingLinearSweptSpheresFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_LINEAR_SWEPT_SPHERES_FEATURES_NV;
#endif
#ifdef VK_NV_cuda_kernel_launch
        cudaKernelLaunchFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_FEATURES_NV_COMPAT;
#endif
#ifdef VK_NV_shader_sm_builtins
        shaderSMBuiltinsFeaturesNV.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV;
#endif
#ifdef VK_VERSION_1_1
        requestedVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
        optionalVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
#endif
#ifdef VK_VERSION_1_2
        requestedVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
        optionalVulkan12Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
#endif
#ifdef VK_VERSION_1_3
        requestedVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
        optionalVulkan13Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
#endif
#ifdef VK_VERSION_1_4
        requestedVulkan14Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
        optionalVulkan14Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES;
#endif
    }
    /// Returns false if a pNext entry is not supported by sgl.
    bool setRequestedFeaturesFromPNextChain(const void* pNext, std::vector<const char*>& requiredDeviceExtensions);
    bool setOptionalFeaturesFromPNextChain(const void* pNext, std::vector<const char*>& optionalDeviceExtensions);
    /// Called by the two functions above.
    bool setExtensionFeaturesFromPNextEntry(const void* pNext, std::vector<const char*>& deviceExtensions);
    VkPhysicalDeviceFeatures requestedPhysicalDeviceFeatures{};
    VkPhysicalDeviceFeatures optionalPhysicalDeviceFeatures{};
    VkPhysicalDeviceTimelineSemaphoreFeatures timelineSemaphoreFeatures{};
    VkPhysicalDeviceBufferDeviceAddressFeatures bufferDeviceAddressFeatures{};
    VkPhysicalDeviceScalarBlockLayoutFeatures scalarBlockLayoutFeatures{};
    VkPhysicalDeviceUniformBufferStandardLayoutFeaturesKHR uniformBufferStandardLayoutFeaturesKhr{};
    VkPhysicalDeviceShaderFloat16Int8Features shaderFloat16Int8Features{};
    VkPhysicalDevice16BitStorageFeatures device16BitStorageFeatures{};
    VkPhysicalDevice8BitStorageFeatures device8BitStorageFeatures{};
    VkPhysicalDeviceShaderDrawParametersFeatures shaderDrawParametersFeatures{};
    VkPhysicalDeviceSubgroupSizeControlFeatures subgroupSizeControlFeatures{};
    VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures{};
    VkPhysicalDeviceRayTracingPipelineFeaturesKHR rayTracingPipelineFeatures{};
    VkPhysicalDeviceRayQueryFeaturesKHR rayQueryFeatures{};
    VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT fragmentShaderInterlockFeatures{};
    VkPhysicalDeviceShaderAtomicInt64FeaturesKHR shaderAtomicInt64Features{};
    VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT shaderImageAtomicInt64Features{};
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT shaderAtomicFloatFeatures{};
#ifdef VK_EXT_mutable_descriptor_type
    VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT mutableDescriptorTypeFeatures{};
#else
    VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT_Compat mutableDescriptorTypeFeatures{};
#endif
#ifdef VK_EXT_shader_atomic_float2
    VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT shaderAtomicFloat2Features{};
#else
    VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT_Compat shaderAtomicFloat2Features{};
#endif
#ifdef VK_KHR_shader_bfloat16
    VkPhysicalDeviceShaderBfloat16FeaturesKHR shaderBfloat16Features{};
#else
    VkPhysicalDeviceShaderBfloat16FeaturesKHR_Compat shaderBfloat16Features{};
#endif
    VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV fragmentShaderBarycentricFeaturesNV{};
    VkPhysicalDeviceMeshShaderFeaturesNV meshShaderFeaturesNV{};
#ifdef VK_EXT_mesh_shader
    VkPhysicalDeviceMeshShaderFeaturesEXT meshShaderFeaturesEXT{};
#else
    VkPhysicalDeviceMeshShaderFeaturesEXT_Compat meshShaderFeaturesEXT{};
#endif
#ifdef VK_NV_cooperative_matrix
    VkPhysicalDeviceCooperativeMatrixFeaturesNV cooperativeMatrixFeaturesNV{};
#else
    VkPhysicalDeviceCooperativeMatrixFeaturesNV_Compat cooperativeMatrixFeaturesNV{};
#endif
#ifdef VK_KHR_cooperative_matrix
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR cooperativeMatrixFeaturesKHR{};
#else
    VkPhysicalDeviceCooperativeMatrixFeaturesKHR_Compat cooperativeMatrixFeaturesKHR{};
#endif
#ifdef VK_NV_cooperative_matrix2
    VkPhysicalDeviceCooperativeMatrix2FeaturesNV cooperativeMatrix2FeaturesNV{};
#else
    VkPhysicalDeviceCooperativeMatrix2FeaturesNV_Compat cooperativeMatrix2FeaturesNV{};
#endif
#ifdef VK_NV_cooperative_vector
    VkPhysicalDeviceCooperativeVectorFeaturesNV cooperativeVectorFeaturesNV{};
#else
    VkPhysicalDeviceCooperativeVectorFeaturesNV_Compat cooperativeVectorFeaturesNV{};
#endif
#ifdef VK_EXT_shader_64bit_indexing
    VkPhysicalDeviceShader64BitIndexingFeaturesEXT shader64BitIndexingFeaturesEXT{};
#else
    VkPhysicalDeviceShader64BitIndexingFeaturesEXT_Compat shader64BitIndexingFeaturesEXT{};
#endif
#ifdef VK_NV_ray_tracing_linear_swept_spheres
    VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV rayTracingLinearSweptSpheresFeaturesNV{};
#else
    VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV_Compat rayTracingLinearSweptSpheresFeaturesNV{};
#endif
#ifdef VK_NV_cuda_kernel_launch
    VkPhysicalDeviceCudaKernelLaunchFeaturesNV cudaKernelLaunchFeaturesNV{};
#else
    VkPhysicalDeviceCudaKernelLaunchFeaturesNV_Compat cudaKernelLaunchFeaturesNV{};
#endif
#ifdef VK_NV_shader_sm_builtins
    VkPhysicalDeviceShaderSMBuiltinsFeaturesNV shaderSMBuiltinsFeaturesNV{};
#else
    VkPhysicalDeviceShaderSMBuiltinsFeaturesNV_Compat shaderSMBuiltinsFeaturesNV{};
#endif
    // The following features have no extensions, thus use
    bool optionalEnableShaderDrawParametersFeatures = false;
    // Vulkan 1.x features are only enabled when at least one value in the struct is set to true.
#ifdef VK_VERSION_1_1
    VkPhysicalDeviceVulkan11Features requestedVulkan11Features{};
    VkPhysicalDeviceVulkan11Features optionalVulkan11Features{};
#else
    VkPhysicalDeviceVulkan11Features_Compat requestedVulkan11Features{};
    VkPhysicalDeviceVulkan11Features_Compat optionalVulkan11Features{};
#endif
#ifdef VK_VERSION_1_2
    VkPhysicalDeviceVulkan12Features requestedVulkan12Features{};
    VkPhysicalDeviceVulkan12Features optionalVulkan12Features{};
#else
    VkPhysicalDeviceVulkan12Features_Compat requestedVulkan12Features{};
    VkPhysicalDeviceVulkan12Features_Compat optionalVulkan12Features{};
#endif
#ifdef VK_VERSION_1_3
    VkPhysicalDeviceVulkan13Features requestedVulkan13Features{};
    VkPhysicalDeviceVulkan13Features optionalVulkan13Features{};
#else
    VkPhysicalDeviceVulkan13Features_Compat requestedVulkan13Features{};
    VkPhysicalDeviceVulkan13Features_Compat optionalVulkan13Features{};
#endif
#ifdef VK_VERSION_1_4
    VkPhysicalDeviceVulkan14Features requestedVulkan14Features{};
    VkPhysicalDeviceVulkan14Features optionalVulkan14Features{};
#else
    VkPhysicalDeviceVulkan14Features_Compat requestedVulkan14Features{};
    VkPhysicalDeviceVulkan14Features_Compat optionalVulkan14Features{};
#endif
};

#endif //SGL_DEVICE_HPP
