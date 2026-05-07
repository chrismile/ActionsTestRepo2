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

#include <iostream>

#include "Device.hpp"

#ifdef __APPLE__
//#define VK_ENABLE_BETA_EXTENSIONS
//#include <vulkan/vulkan_beta.h>
#endif

bool DeviceFeatures::setExtensionFeaturesFromPNextEntry(
        const void* pNext, std::vector<const char*>& deviceExtensions) {
    auto* baseStructurePtr = reinterpret_cast<const VkBaseInStructure*>(pNext);
    VkStructureType structureType = baseStructurePtr->sType;
    if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_TIMELINE_SEMAPHORE_FEATURES) {
        this->timelineSemaphoreFeatures =
                *reinterpret_cast<const VkPhysicalDeviceTimelineSemaphoreFeatures*>(pNext);
        if (this->timelineSemaphoreFeatures.timelineSemaphore) {
            deviceExtensions.push_back(VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES) {
        this->bufferDeviceAddressFeatures =
                *reinterpret_cast<const VkPhysicalDeviceBufferDeviceAddressFeatures*>(pNext);
        if (this->bufferDeviceAddressFeatures.bufferDeviceAddress) {
            deviceExtensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES) {
        this->scalarBlockLayoutFeatures =
                *reinterpret_cast<const VkPhysicalDeviceScalarBlockLayoutFeatures*>(pNext);
        if (this->scalarBlockLayoutFeatures.scalarBlockLayout) {
            deviceExtensions.push_back(VK_EXT_SCALAR_BLOCK_LAYOUT_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFORM_BUFFER_STANDARD_LAYOUT_FEATURES) {
        this->uniformBufferStandardLayoutFeaturesKhr =
                *reinterpret_cast<const VkPhysicalDeviceUniformBufferStandardLayoutFeatures*>(pNext);
        if (this->uniformBufferStandardLayoutFeaturesKhr.uniformBufferStandardLayout) {
            deviceExtensions.push_back(VK_KHR_UNIFORM_BUFFER_STANDARD_LAYOUT_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_FLOAT16_INT8_FEATURES) {
        this->shaderFloat16Int8Features =
                *reinterpret_cast<const VkPhysicalDeviceShaderFloat16Int8Features*>(pNext);
        if (this->shaderFloat16Int8Features.shaderFloat16 ||this->shaderFloat16Int8Features.shaderInt8) {
            deviceExtensions.push_back(VK_KHR_SHADER_FLOAT16_INT8_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_16BIT_STORAGE_FEATURES) {
        this->device16BitStorageFeatures =
                *reinterpret_cast<const VkPhysicalDevice16BitStorageFeatures*>(pNext);
        if (this->device16BitStorageFeatures.storageBuffer16BitAccess
                || this->device16BitStorageFeatures.uniformAndStorageBuffer16BitAccess
                || this->device16BitStorageFeatures.storagePushConstant16
                || this->device16BitStorageFeatures.storageInputOutput16) {
            deviceExtensions.push_back(VK_KHR_16BIT_STORAGE_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_8BIT_STORAGE_FEATURES) {
        this->device8BitStorageFeatures =
                *reinterpret_cast<const VkPhysicalDevice8BitStorageFeatures*>(pNext);
        if (this->device8BitStorageFeatures.storageBuffer8BitAccess
                || this->device8BitStorageFeatures.uniformAndStorageBuffer8BitAccess
                || this->device8BitStorageFeatures.storagePushConstant8) {
            deviceExtensions.push_back(VK_KHR_8BIT_STORAGE_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_DRAW_PARAMETERS_FEATURES) {
        this->shaderDrawParametersFeatures =
                *reinterpret_cast<const VkPhysicalDeviceShaderDrawParameterFeatures*>(pNext);
        if (this->shaderDrawParametersFeatures.shaderDrawParameters) {
            optionalEnableShaderDrawParametersFeatures = true;
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_FEATURES) {
        this->subgroupSizeControlFeatures =
                *reinterpret_cast<const VkPhysicalDeviceSubgroupSizeControlFeatures*>(pNext);
        if (this->subgroupSizeControlFeatures.subgroupSizeControl) {
            deviceExtensions.push_back(VK_EXT_SUBGROUP_SIZE_CONTROL_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR) {
        this->accelerationStructureFeatures =
                *reinterpret_cast<const VkPhysicalDeviceAccelerationStructureFeaturesKHR*>(pNext);
        if (this->accelerationStructureFeatures.accelerationStructure) {
            deviceExtensions.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR) {
        this->rayTracingPipelineFeatures =
                *reinterpret_cast<const VkPhysicalDeviceRayTracingPipelineFeaturesKHR*>(pNext);
        if (this->rayTracingPipelineFeatures.rayTracingPipeline) {
            deviceExtensions.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_QUERY_FEATURES_KHR) {
        this->rayQueryFeatures =
                *reinterpret_cast<const VkPhysicalDeviceRayQueryFeaturesKHR*>(pNext);
        if (this->rayQueryFeatures.rayQuery) {
            deviceExtensions.push_back(VK_KHR_RAY_QUERY_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_INTERLOCK_FEATURES_EXT) {
        this->fragmentShaderInterlockFeatures =
                *reinterpret_cast<const VkPhysicalDeviceFragmentShaderInterlockFeaturesEXT*>(pNext);
        if (this->fragmentShaderInterlockFeatures.fragmentShaderPixelInterlock) {
            deviceExtensions.push_back(VK_EXT_FRAGMENT_SHADER_INTERLOCK_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_INT64_FEATURES_KHR) {
        this->shaderAtomicInt64Features =
                *reinterpret_cast<const VkPhysicalDeviceShaderAtomicInt64Features*>(pNext);
        if (this->shaderAtomicInt64Features.shaderBufferInt64Atomics
                || this->shaderAtomicInt64Features.shaderSharedInt64Atomics) {
            deviceExtensions.push_back(VK_KHR_SHADER_ATOMIC_INT64_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_IMAGE_ATOMIC_INT64_FEATURES_EXT) {
        this->shaderImageAtomicInt64Features =
                *reinterpret_cast<const VkPhysicalDeviceShaderImageAtomicInt64FeaturesEXT*>(pNext);
        if (this->shaderImageAtomicInt64Features.shaderImageInt64Atomics
                || this->shaderImageAtomicInt64Features.sparseImageInt64Atomics) {
            deviceExtensions.push_back(VK_EXT_SHADER_IMAGE_ATOMIC_INT64_EXTENSION_NAME);
        }
    }
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_FEATURES_EXT) {
        this->shaderAtomicFloatFeatures =
                *reinterpret_cast<const VkPhysicalDeviceShaderAtomicFloatFeaturesEXT*>(pNext);
        if (this->shaderAtomicFloatFeatures.shaderBufferFloat32Atomics) {
            deviceExtensions.push_back(VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME);
        }
    }
#ifdef VK_EXT_mutable_descriptor_type
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MUTABLE_DESCRIPTOR_TYPE_FEATURES_EXT) {
        this->mutableDescriptorTypeFeatures =
                *reinterpret_cast<const VkPhysicalDeviceMutableDescriptorTypeFeaturesEXT*>(pNext);
        if (this->mutableDescriptorTypeFeatures.mutableDescriptorType) {
            deviceExtensions.push_back(VK_EXT_MUTABLE_DESCRIPTOR_TYPE_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_EXT_shader_atomic_float2
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_ATOMIC_FLOAT_2_FEATURES_EXT) {
        this->shaderAtomicFloat2Features =
                *reinterpret_cast<const VkPhysicalDeviceShaderAtomicFloat2FeaturesEXT*>(pNext);
        if (this->shaderAtomicFloat2Features.shaderBufferFloat32AtomicMinMax) {
            deviceExtensions.push_back(VK_EXT_SHADER_ATOMIC_FLOAT_2_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_KHR_shader_bfloat16
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_BFLOAT16_FEATURES_KHR) {
        this->shaderBfloat16Features =
                *reinterpret_cast<const VkPhysicalDeviceShaderBfloat16FeaturesKHR*>(pNext);
        if (this->shaderBfloat16Features.shaderBFloat16Type) {
            deviceExtensions.push_back(VK_KHR_SHADER_BFLOAT16_EXTENSION_NAME);
        }
    }
#endif
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_NV) {
        this->meshShaderFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceMeshShaderFeaturesNV*>(pNext);
        if (this->meshShaderFeaturesNV.meshShader) {
            deviceExtensions.push_back(VK_NV_MESH_SHADER_EXTENSION_NAME);
        }
    }
#ifdef VK_EXT_mesh_shader
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_MESH_SHADER_FEATURES_EXT) {
        this->meshShaderFeaturesEXT =
                *reinterpret_cast<const VkPhysicalDeviceMeshShaderFeaturesEXT*>(pNext);
        if (this->meshShaderFeaturesEXT.meshShader) {
            deviceExtensions.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
        }
    }
#endif
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADER_BARYCENTRIC_FEATURES_NV) {
        this->fragmentShaderBarycentricFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceFragmentShaderBarycentricFeaturesNV*>(pNext);
        if (this->fragmentShaderBarycentricFeaturesNV.fragmentShaderBarycentric) {
            deviceExtensions.push_back(VK_NV_FRAGMENT_SHADER_BARYCENTRIC_EXTENSION_NAME);
        }
    }
#ifdef VK_NV_cooperative_matrix
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_NV) {
        this->cooperativeMatrixFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceCooperativeMatrixFeaturesNV*>(pNext);
        if (this->cooperativeMatrixFeaturesNV.cooperativeMatrix) {
            deviceExtensions.push_back(VK_NV_COOPERATIVE_MATRIX_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_KHR_cooperative_matrix
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_FEATURES_KHR) {
        this->cooperativeMatrixFeaturesKHR =
                *reinterpret_cast<const VkPhysicalDeviceCooperativeMatrixFeaturesKHR*>(pNext);
        if (this->cooperativeMatrixFeaturesKHR.cooperativeMatrix) {
            deviceExtensions.push_back(VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_NV_cooperative_matrix2
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_MATRIX_2_FEATURES_NV) {
        this->cooperativeMatrix2FeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceCooperativeMatrix2FeaturesNV*>(pNext);
        if (this->cooperativeMatrix2FeaturesNV.cooperativeMatrixWorkgroupScope) {
            deviceExtensions.push_back(VK_NV_COOPERATIVE_MATRIX_2_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_NV_cooperative_vector
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_COOPERATIVE_VECTOR_FEATURES_NV) {
        this->cooperativeVectorFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceCooperativeVectorFeaturesNV*>(pNext);
        if (this->cooperativeVectorFeaturesNV.cooperativeVector) {
            deviceExtensions.push_back(VK_NV_COOPERATIVE_VECTOR_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_EXT_shader_64bit_indexing
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_64_BIT_INDEXING_FEATURES_EXT) {
        this->shader64BitIndexingFeaturesEXT =
                *reinterpret_cast<const VkPhysicalDeviceShader64BitIndexingFeaturesEXT*>(pNext);
        if (this->shader64BitIndexingFeaturesEXT.shader64BitIndexing) {
            deviceExtensions.push_back(VK_EXT_SHADER_64BIT_INDEXING_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_NV_ray_tracing_linear_swept_spheres
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_LINEAR_SWEPT_SPHERES_FEATURES_NV) {
        this->rayTracingLinearSweptSpheresFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV*>(pNext);
        if (this->rayTracingLinearSweptSpheresFeaturesNV.spheres
                || this->rayTracingLinearSweptSpheresFeaturesNV.linearSweptSpheres) {
            deviceExtensions.push_back(VK_NV_RAY_TRACING_LINEAR_SWEPT_SPHERES_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_NV_cuda_kernel_launch
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_CUDA_KERNEL_LAUNCH_FEATURES_NV_COMPAT) {
        this->cudaKernelLaunchFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceCudaKernelLaunchFeaturesNV*>(pNext);
        if (this->cudaKernelLaunchFeaturesNV.cudaKernelLaunchFeatures) {
            deviceExtensions.push_back(VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME);
        }
    }
#endif
#ifdef VK_NV_shader_sm_builtins
    else if (structureType == VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_SM_BUILTINS_FEATURES_NV) {
        this->shaderSMBuiltinsFeaturesNV =
                *reinterpret_cast<const VkPhysicalDeviceShaderSMBuiltinsFeaturesNV*>(pNext);
        if (this->shaderSMBuiltinsFeaturesNV.shaderSMBuiltins) {
            deviceExtensions.push_back(VK_NV_SHADER_SM_BUILTINS_EXTENSION_NAME);
        }
    }
#endif
    else {
        return false;
    }
    return true;
}

int main() {
    std::cout << "Hello World" << std::endl;
    return 0;
}