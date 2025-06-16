import { z } from "zod";


export const configSchema = z.object({
    espId: z.number().positive().optional(),
    field: z.string().min(1, "Field name is required"),
    groupId: z.number().positive().optional(),
    value: z.string().default("")
});

export type Config = z.infer<typeof configSchema>
