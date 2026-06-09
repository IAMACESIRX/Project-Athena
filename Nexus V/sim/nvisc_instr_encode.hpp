#pragma once
#include <cstdint>

static constexpr uint8_t NV_OP_NOP    = 0x00;
static constexpr uint8_t NV_OP_ALU    = 0x01;
static constexpr uint8_t NV_OP_LOAD   = 0x02;
static constexpr uint8_t NV_OP_STORE  = 0x03;
static constexpr uint8_t NV_OP_BRANCH = 0x04;
static constexpr uint8_t NV_OP_CSR    = 0x05;

static inline uint32_t nvenc_r_full(
    uint8_t opcode,
    uint8_t rd,
    uint8_t funct3,
    uint8_t rs1,
    uint8_t rs2,
    uint8_t funct7
) {
    uint32_t instr = 0;
    instr |= uint32_t(opcode & 0x7F);
    instr |= uint32_t(rd     & 0x1F) << 7;
    instr |= uint32_t(funct3 & 0x07) << 12;
    instr |= uint32_t(rs1    & 0x1F) << 15;
    instr |= uint32_t(rs2    & 0x1F) << 20;
    instr |= uint32_t(funct7 & 0x7F) << 25;
    return instr;
}

static inline uint32_t nvenc_r(uint8_t opcode, uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(opcode, rd, 0, rs1, rs2, 0);
}

static inline uint32_t nvenc_add(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b000, rs1, rs2, 0b0000000);
}

static inline uint32_t nvenc_sub(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b000, rs1, rs2, 0b0100000);
}

static inline uint32_t nvenc_and(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b111, rs1, rs2, 0b0000000);
}

static inline uint32_t nvenc_or(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b110, rs1, rs2, 0b0000000);
}

static inline uint32_t nvenc_xor(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b100, rs1, rs2, 0b0000000);
}

static inline uint32_t nvenc_slt(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    return nvenc_r_full(NV_OP_ALU, rd, 0b010, rs1, rs2, 0b0000000);
}

static inline uint32_t nvenc_i(uint8_t opcode, uint8_t rd, uint8_t rs1, uint16_t imm12) {
    uint32_t instr = 0;
    instr |= uint32_t(opcode & 0x7F);
    instr |= uint32_t(rd  & 0x1F) << 7;
    instr |= uint32_t(rs1 & 0x1F) << 15;
    instr |= uint32_t(imm12 & 0x0FFF) << 20;
    return instr;
}

static inline uint32_t nvenc_s(uint8_t opcode, uint8_t rs1, uint8_t rs2, uint16_t imm12) {
    uint32_t instr = 0;
    uint32_t imm = uint32_t(imm12 & 0x0FFF);

    instr |= uint32_t(opcode & 0x7F);
    instr |= (imm & 0x1F) << 7;
    instr |= uint32_t(rs1 & 0x1F) << 15;
    instr |= uint32_t(rs2 & 0x1F) << 20;
    instr |= ((imm >> 5) & 0x7F) << 25;
    return instr;
}

static inline uint32_t nvenc_b(uint8_t opcode, uint8_t rs1, uint8_t rs2, uint16_t imm12) {
    return nvenc_s(opcode, rs1, rs2, imm12);
}

static inline uint32_t nvenc_csr(uint8_t opcode, uint8_t rd, uint16_t csr_addr) {
    return nvenc_i(opcode, rd, 0, csr_addr);
}

static inline uint32_t nvenc_nop() {
    return nvenc_r_full(NV_OP_NOP, 0, 0, 0, 0, 0);
}
