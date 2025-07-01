import { z } from "zod";


export const configSchema = z.object({
    espId: z.number().positive().optional(),
    field: z.string().min(1, "Field name is required"),
    groupId: z.number().positive().optional().nullable(),
    value: z.string().default("")
});

export type Config = z.infer<typeof configSchema>

export const configWithIdSchema = configSchema.extend({
    id: z.number().positive("The id must be positive")
});

export type ConfigWithId = z.infer<typeof configWithIdSchema>

export const genericConfigSchema = configSchema.extend({
    id: z.number().positive("The id must be positive").optional()
});

export type GenericConfigSchema = z.infer<typeof genericConfigSchema>
